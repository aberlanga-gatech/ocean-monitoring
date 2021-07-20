# ocean-monitoring
Ocean Monitoring Repo

Made by Alfredo Berlanga
AGPL-3.0 License
Last edit July 2, 2021


## DESCRIPTION

Repository for all the files to be used in the OceanMonitoring MQTT data transfer system to stream data to the cloud.


## FOLDERS

cloud_test --> main folder
SEE README

## MQTT Connection

Topic: om/telemetry

Host: our beloved AWS server :)

The payload data is described in [this JSON file](https://github.com/aberlanga-gatech/ocean-monitoring/blob/main/dataframe_example.json)

## TODO


## DEPENDENCIES

Arduino libraries used:
  - ESP32 Client (WiFi.h)
  - PubSubClient (PubSubClient.h)
