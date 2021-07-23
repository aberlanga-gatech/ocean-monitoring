# ocean-monitoring
Ocean Monitoring Repo

Made by Alfredo Berlanga
AGPL-3.0 License
Last edit July 2, 2021


## DESCRIPTION

Repository for all the files to be used in the OceanMonitoring MQTT data transfer system to stream data to the cloud.


## FOLDERS

cloud_test     --> main internet stuff/dashboard folder
raspberry-pi   --> main data uplink and telemetry folder
ESP8266        --> learning materials (not used)
mqtt_attempt_1 --> obsolete attempt at data uplink and telemetry (not used)

## MQTT Connection

Topic: om/telemetry

Host: our beloved AWS server :)

The payload data is described in [this JSON file](https://github.com/aberlanga-gatech/ocean-monitoring/blob/main/dataframe_example.json)

## TODO


## DEPENDENCIES

Arduino libraries used:
  - ESP32 Client (WiFi.h)
  - PubSubClient (PubSubClient.h)
