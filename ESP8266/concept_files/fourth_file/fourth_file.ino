// this file is taken from the previous
// it shows added functionality with sensors and stuff
// read files one through three for context

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN D1
#define CLIENT_ID "ESP8266_CLIENT"

const char* ssid = "ssid_name";
const char* password = "password";
const char* mqtt_server = "web.server.com";
DHT dht(DHTPIN, DHT11, 15);

WiFiClient espClient; // initialize wifi client object
PubSubClient client(espClient); // initialize mqtt client
unsigned long lastMsg = 0;
char temp[50]; // allocate space for temperature reads
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int val = 0;


void setup_wifi(){
  delay(10);
  Serial.println(); // print empty line to demarcate connection attempt
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // define wifi connection security mode
  WiFi.begin(ssid, password); // connect to wifi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // print dots every .5 seconds until connected
  }

  randomSeed(micros()); // generates a seed for RNG using the ms since star of program as entropy
  
  Serial.println("");
  Serial.println("Connection to WiFi successful");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic: "); // println "Topic: [topic]"
  Serial.println(topic);
  Serial.print("Message: "); // println "Message: [msg]"
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // perform physical feedback response to 1 received as first char
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW); // set the built-in mcu led ON (yeah, low, its weird)
    digitalWrite(D1, HIGH); // send 1 voltage to pin D1
    digitalWrite(D2, HIGH); // ditto to pin D2
  } else { // do the opposite
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
  }
}


void reconnect() {
  // retries connection to mqtt if still not connected
  // throw exception if takes too long
  while (!client.connected()) {
    Serial.println("Attempting to connect to MQTT broker");
    // attempts do connect
    if (client.connect(CLIENT_ID)) {
      Serial.println("Connected");
      // publish connection method to placeholder topic
      client.publish("PHoldTopic", "TESTING CONNECTION");
      client.subscribe("inPHold_Topic");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println("Try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
  // pins configs
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(115200); // common value for NodeMCU
  setup_wifi(); // setup wifi connection (internet link)
  client.setServer(mqtt_server, 1883); // server address, port
  client.setCallback(callback); // ref to callback() func (on_message equiv.)
}


void loop() {
  if (!client.connected()) {
    reconnect(); // perform reconnect loop
  }
  client.loop(); // perform this function on mcu client (a lil recursion) in case of failure

  int t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to obtain reading");
    delay(1000);
    return;
  }
  
  unsigned long now = millis(); // how many millis since this was instanced
  /* artificial delay: lets the loop run (thus checking connection failures)
   *  but only publishes every 5 seconds
   *  i.e. if last message wass received more than 5 seconds ago...
   */
  if (now - lastMsg > 5000) {
    lastMsg = now; // make the last message
    ++val; // increment message counter
    snprintf (temp, 75, "%1d", t); // assign t to temp with max size 75 and then sprintf
    Serial.print("Publishing message: ");
    Serial.println(temp); // display what message is to be published
    client.publish("PHolder_Topic", temp); // publish to the placeholder topic
    delay(100);
  }
}
