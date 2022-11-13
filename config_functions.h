#ifndef CONFIG_FUNCTIONS_H
#define CONFIG_FUNCTIONS_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h> 
#include "global_variables.h"

bool readConfigurationParameters();
bool saveConfigurationParameters();



#endif
