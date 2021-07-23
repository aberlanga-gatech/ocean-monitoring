from flask import Flask
from flask_cors import CORS, cross_origin
import psycopg2
import psycopg2.extras
import json
import configparser
import random


def get_idx(elem):
	return elem[0]

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
	indexer = 0
	
	for reg in telemetry_cursor:
		temperature.append([indexer,reg["temperature"]])
		pressure.append([indexer,reg["pressure"]])
		ph.append([indexer,reg["ph"]])
		oxigen.append([indexer ,reg["o2"]])
		indexer = indexer + 1

	temperature.sort(key=get_idx, reverse=True)
	pressure.sort(key=get_idx, reverse=True)
	ph.sort(key=get_idx, reverse=True)
	oxigen.sort(key=get_idx, reverse=True)


	data = {
		"temperature" : temperature,
		"pressure" : pressure,
		"ph" : ph,
		"oxygen" : oxigen,
	}

	return data
    