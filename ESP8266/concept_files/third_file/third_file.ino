// combining knowledge of protocols and mcu
// to upload to a server such as ThingSpeak, ESP8266WiFi.h and DHT.h are needed
// for thingSpeak you need an API key to pull API requests

// to upload data from NodeMCU to a server using mqtt, we need to import ESP8266WiFi and PubSubClient
// the following is an example of a connection
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "ssid_name";
const char *password = "password";
const char *mqtt_server = "web.server.com";

WiFiClient espClient;           // initialize wifi client object
PubSubClient client(espClient); // initialize mqtt client
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int val = 0;

void setup_wifi()
{
  delay(10);
  Serial.println(); // print empty line to demarcate connection attempt
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);        // define wifi connection security mode
  WiFi.begin(ssid, password); // connect to wifi

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); // print dots every .5 seconds until connected
  }

  randomSeed(micros()); // generates a seed for RNG using the ms since star of program as entropy

  Serial.println("");
  Serial.println("Connection to WiFi successful");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Topic: "); // println "Topic: [topic]"
  Serial.println(topic);
  Serial.print("Message: "); // println "Message: [msg]"
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // perform physical feedback response to 1 received as first char
  if ((char)payload[0] == '1')
  {
    digitalWrite(BUILTIN_LED, LOW); // set the built-in mcu led ON (yeah, low, its weird)
    digitalWrite(D1, HIGH);         // send 1 voltage to pin D1
    digitalWrite(D2, HIGH);         // ditto to pin D2
  }
  else
  { // do the opposite
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
  }
}

void reconnect()
{
  // retries connection to mqtt if still not connected
  // throw exception if takes too long
  while (!client.connected())
  {
    Serial.println("Attempting to connect to MQTT broker");
    // generate random client ID to keep trying with different aliases
    String clientID = "ESP_Client_";
    clientID += String(random(0xffff), HEX);
    // attempts do connect
    if (client.connect(clientID.c_str()))
    {
      Serial.println("Connected");
      // publish connection method to placeholder topic
      client.publish("PHoldTopic", "TESTING CONNECTION");
      client.subscribe("inPHold_Topic");
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println("Try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  // pins configs
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(115200);                // common value for NodeMCU
  setup_wifi();                        // setup wifi connection (internet link)
  client.setServer(mqtt_server, 1883); // server address, port
  client.setCallback(callback);        // ref to callback() func (on_message equiv.)
}

void loop()
{
  if (!client.connected())
  {
    reconnect(); // perform reconnect loop
  }
  client.loop(); // perform this function on mcu client (a lil recursion) in case of failure

  unsigned long now = millis(); // how many millis since this was instanced
  /* artificial delay: lets the loop run (thus checking connection failures)
   *  but only publishes every 2 seconds
   *  i.e. if last message wass received more than 2 seconds ago...
   */
  if (now - lastMsg > 2000)
  {
    lastMsg = now; // make the last message
    ++val;         // increment message counter
    snprintf(msg, MSG_BUFFER_SIZE, "msg number %1d", val);
    Serial.print("Publishing message: ");
    Serial.println(msg);                  // display what message is to be published
    client.publish("PHolder_Topic", msg); // publish to the placeholder topic
  }
}
