import paho.mqtt.client as mqtt
import json
import psycopg2
import configparser


print("== Ocean's Monitoring MQTT Handler ==")

#load configuration
print("Loading config...")
config = configparser.ConfigParser(interpolation=None)
config.read('config.ini')

DB_PASSWORD = config['database']['password']
DB_HOST = config['database']['host']
DB_USER = config['database']['username']
DB_NAME = config['database']['dbname']

MQTT_HOST = config['mqtt']['host']
MQTT_TOPIC = config['mqtt']['topic']

print(MQTT_TOPIC)

#connect to database
print("Connecting db...")
conn = psycopg2.connect(dbname=DB_NAME, user=DB_USER, host=DB_HOST, password=DB_PASSWORD)
cur_insert = conn.cursor()

# the client is connected
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("om/telemetry")

# message received
def on_message(client, userdata, msg):

    #convert payload to json object
    payload = json.loads(msg.payload)
    print("La temperatura hoy:", payload['temperature'])

    #save to db
    dbrow = (payload['device_id'], payload['temperature'], payload['pressure'], payload['ph'], payload['oxygen'],payload['lat'],payload['lng'])
    cur_insert.execute("INSERT INTO telemetry(time,device_id,temperature,pressure,ph,o2,lat,lng) VALUES (NOW(),%s,%s,%s,%s,%s,%s,%s)", dbrow)
    conn.commit()

#client configuration
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_HOST, 1883, 60)

#blocking loop
client.loop_forever()