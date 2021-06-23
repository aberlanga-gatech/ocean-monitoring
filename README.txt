# ocean-monitoring
Ocean Monitoring Repo

Made by Alfredo Berlanga
AGPL-3.0 License
Last edit June 23, 2021


## DESCRIPTION

Repository for all the files to be used in the OceanMonitoring MQTT data transfer system to stream data to the cloud.

## FOLDERS

ESP8266 -- Main Folder
  -> intro_files -- notes on how NodeMCU works.
  -> concept_files -- sample proof of concept files for MQTT system.
      ->> third_file -- simple MQTT protocol set up with a non-existent placeholder server.
      ->> fourth_file -- concept MQTT protocol that uses AdaFruit DHT library to send temperature readings via MQTT.

## TODO
  - Configure HiveMQ or similar dashboard-oriented MQTT broker for testing.
      - MS Azure and AWS don't have strong (or free) MQTT-oriented frameworks.
      - Alternative would be to develop a dashboard using something like ThingsBoard.
  - Acquire ESP8266 (NodeMCU) and adapt code to specific sensors/implementation of the MCU.
      - NodeMCU and sensors (not necessarily DHT, code can be adapted to any type of sensor).
      - In the case that the sensors will not be used directly in the Node, program the intake of data implementation.
  - Optimize code to reduce compile times (maybe consider reducing the amount of global variables).

## DEPENDENCIES

Arduino libraries used:
  - AdaFruit DHT_sensor_library (DHT.h)
  - EspMQTTClient (ESP8266WiFi.h)
  - PubSubClient (PubSubClient.h)
