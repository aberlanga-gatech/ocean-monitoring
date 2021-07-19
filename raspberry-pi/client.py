import paho.mqtt.client as mqtt
import json
import configparser
from time import sleep
import random
#TODO: include RBPi specific libraries for data acquisition


#load configuration
print("Loading config...")
config = configparser.ConfigParser(interpolation=None)
config.read('config.ini')

MQTT_HOST = config['mqtt']['host']
MQTT_TOPIC = config['mqtt']['topic']

# the client is connected
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

#client config
client = mqtt.Client()
client.on_connect = on_connect

print("MQTT Connecting...")
client.connect(MQTT_HOST, 1883, 60)


print("Entering data accquisition loop...")

while(True):

	#TODO: accquire data from sensors

	#create payload
	#TODO: replace random with actual data
	packet = {
		"device_id" : "A1B2C3D4",
		"temperature" : random.uniform(10.250, 18.356),
		"pressure" : random.uniform(90, 300),
		"ph" : random.uniform(5.8,7.5),
		"o2" : random.uniform(100,200),
		"lat" : 19.4238932,
		"lng" : -99.1857167
	}

	payload = json.dumps(packet)
	print(payload)

	#publish
	print("Publishing...")
	client.publish("om/telemetry", payload=payload, qos=0, retain=False)

	#every 2 seconds
	sleep(2)

client.disconnect()

print("Bye!")
