#ifndef MEASUREMENT_FUNCTIONS_H
#define MEASUREMENT_FUNCTIONS_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "global_variables.h"

void updateCounter();
void measureValues();
void checkWaterLevel();
int32_t measureRssi();
void measureHumidity(bool doMeasurement);
void measureWaterLevel(bool doMeasurement);

#endif
