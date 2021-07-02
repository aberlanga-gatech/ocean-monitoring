#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi connection
const char *ssid = "placehold";
const char *password = "placehold";

// MQTT server stuff
const char *mqtt_server = "driver.cloudmqtt.com";
const int mqtt_port = 18678;
const char *mqtt_user = "lvumygpt";
const char *mqtt_pass = "JyCVNlyqGHQf";

const char *mainTopic = "Main_Topic";
const char *controlTopic = "control_topic";

boolean state = true;

// Wifi globals
WiFiClient espClient;
PubSubClient client(espClient);

// Message globals
unsigned long lastMsg = 0;
String toSend;
char buf[3];

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

    Serial.println("");
    Serial.println("Connection to WiFi successful");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String incoming = "";
    Serial.print("Topic: "); // println "Topic: [topic]"
    Serial.println(topic);
    Serial.print("Message: "); // println "Message: [msg]"
    for (int i = 0; i < length; i++)
    {
        incoming += (char)payload[i];
    }
    incoming.trim();
    Serial.println(incoming);
    Serial.println();

    String topicStr(topic);

    if (topicStr.equals(controlTopic))
    {
        if (incoming == "0")
        {
            state = false;
        }
        if (incoming == "1")
        {
            state = true;
        }
    }
}

void reconnect()
{
    // retries connection to mqtt if still not connected
    // throw exception if takes too long
    while (!client.connected())
    {
        Serial.println("Attempting to connect to MQTT broker");

        String clientID = "ESP_Client_";
        clientID += String(random(0xffff), HEX);

        if (client.connect(clientID.c_str(), mqtt_user, mqtt_pass))
        {
            Serial.println("Connected");
            // publish connection method to placeholder topic
            client.publish("xd", "TESTING CONNECTION");
            client.subscribe(controlTopic);
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
    Serial.begin(115200);                     // common value for NodeMCU
    setup_wifi();                             // setup wifi connection (internet link)
    client.setServer(mqtt_server, mqtt_port); // server address, port
    client.setCallback(callback);             // ref to callback() func (on_message equiv.)
}

void loop()
{
    if (!client.connected())
    {
        reconnect(); // perform reconnect loop
    }
    client.loop(); // perform this function on mcu client (a lil recursion) in case of failure

    toSend = String(random(300));
    toSend.toCharArray(buf, 3);
    if (state)
    {
        if (millis() - lastMsg > 2000)
        {
            lastMsg = millis();
            Serial.print("Publishing message: ");
            Serial.println(toSend);         // display what message is to be published
            client.publish(mainTopic, buf); // publish to the placeholder topic
        }
    }
}
