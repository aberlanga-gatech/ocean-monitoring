from flask import Flask
from flask_cors import CORS, cross_origin
import psycopg2
import psycopg2.extras
import json
import configparser
import random


#load configuration
print("Loading config...")
config = configparser.ConfigParser(interpolation=None)
config.read('config.ini')

DB_PASSWORD = config['database']['password']
DB_HOST = config['database']['host']
DB_USER = config['database']['username']
DB_NAME = config['database']['dbname']


#connect to database
print("Connecting db...")
conn = psycopg2.connect(dbname=DB_NAME, user=DB_USER, host=DB_HOST, password=DB_PASSWORD)
telemetry_cursor = conn.cursor(cursor_factory = psycopg2.extras.DictCursor)

print("Dispatching app...")

app = Flask(__name__)

CORS(app)

@app.route("/data")
@cross_origin()
def data():

	telemetry_cursor.execute("SELECT * FROM telemetry order by time desc limit 20")

	temperature = []
	pressure = []
	ph = []
	oxigen = []

	for reg in telemetry_cursor:
		temperature.append([0,reg["temperature"]])
		pressure.append([0,reg["pressure"]])
		ph.append([0,reg["ph"]])
		oxigen.append([0,reg["o2"]])


	data = {
		"temperature" : values,
		"pressure" : pressure,
		"ph" : ph,
		"oxigen" : oxigen,
	}

	return data
    