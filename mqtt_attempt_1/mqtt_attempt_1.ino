/* Made by Alfredo Berlanga
 * alfredo@propelland.com
 * Simple code based on the tutorial at https://www.digikey.com/en/maker/blogs/2018/how-to-use-basic-mqtt-on-arduino
 * Basic environment setup for a Arduino-EthernetShield MQTT system that sends a simple message on a single topic
 * All server domains and addresses are placeholders
 */

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// message function callback definition
void subscribeReceive(char* topic, byte* payload, unsigned int length);

// MAC and IP setup (server)
byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
IPAddress ip(192, 168, 0, 000);

// server address
const char* SERVER = "dom.address.com";

// init ethernet and MQTT objects
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

// setup method
void setup() {
  // begin serial at 9600 clocks
  Serial.begin(9600);

  // ethernet protocol start
  Ethernet.begin(mac, ip);

  // ethernet boot intermission
  delay(3000);

  // set server domain (and port?)
  mqttClient.setServer(SERVER, 1883);


  // establish server connection with given ID (placeholder myID)
  if (mqttClient.connect("myID")) {
    Serial.println("Connection established successfully");

     // subscribe event callback assign
     mqttClient.setCallback(subscribeReceive);
  } else {
    Serial.println("Server connection failed");
  }
}

// main loop
void loop() {
  // continuously scan for messages (recursion)
  mqttClient.loop();

  // subscribe to placeholder topic "pHoldTopic"
  mqttClient.subscribe("pHoldTopic");

  // publish HelloWorld message to pHoldTopic (transfer data).
  /* This if statement is used to send the desired data under the desired topic 
   * can be replaced with anything, see .publish() documentation under PubSubClient for details
   * publishing always done with a simple exemption if-else handler
   */
  if(mqttClient.publish("pHoldTopic", "Hello World")) {
    Serial.println("Message published successfully");
  } else {
    Serial.println("Could not publish message");
  }
  
  // prevent server overload
  delay(4000);

}
