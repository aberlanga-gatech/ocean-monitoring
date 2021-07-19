# ocean-monitoring
Ocean Monitoring Repo

Made by Alfredo Berlanga
AGPL-3.0 License
Last edit July 2, 2021


## DESCRIPTION

Repository for all the files to be used in the OceanMonitoring MQTT data transfer system to stream data to the cloud.


## FOLDERS

ESP8266 -- Main Folder
  -> intro_files -- notes on how NodeMCU works.
  -> concept_files -- sample proof of concept files for MQTT system.
      ->> third_file -- simple MQTT protocol set up with a non-existent placeholder server.
      ->> fourth_file -- concept MQTT protocol that uses AdaFruit DHT library to send temperature readings via MQTT.
  -> cloud_test -- first stable prototype files
      ->> contains the rng_sender file which sends random values to the broker
      ->> contains the dashboard html to control and display the random values
      ->> functionality to start/stop the data stream

## MQTT Connection

Topic: om/telemetry

Host: our beloved AWS server :)

## TODO


## DEPENDENCIES

Arduino libraries used:
  - ESP32 Client (WiFi.h)
  - PubSubClient (PubSubClient.h)
