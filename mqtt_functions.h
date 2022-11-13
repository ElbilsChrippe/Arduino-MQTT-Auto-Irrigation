#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "global_variables.h"
#include "pump_functions.h"
#include "config_functions.h"

void callback(char* topic, byte* payload, unsigned int length);
void parseConfMessage(String jsonString);
void parseCmdMessage(String jsonString);
void publishValues();
void publishMeasValues();
void publishConfValues();
String bToStr(bool inputBool);
void sendAvailabilityDiscoveryMsg();
void sendDistanceDiscoveryMsg();
void sendHumidityDiscoveryMsg();
void sendRssiDiscoveryMsg();
void sendCounterDiscoveryMsg();
void sendMotorstateDiscoveryMsg();
void sendlastPumpDurationDiscoveryMsg();



#endif
