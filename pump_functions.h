#ifndef PUMP_FUNCTIONS_H
#define PUMP_FUNCTIONS_H
#include <Arduino.h>
#include "global_variables.h"
#include "measurement_functions.h"
#include "mqtt_functions.h"

void pumpWater(float waterVolume);
bool checkPumpConditions(float humidity, float waterLevel);
void turnPumpOn();
void turnPumpOff();



#endif
