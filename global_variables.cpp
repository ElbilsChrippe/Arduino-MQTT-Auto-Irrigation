#include "global_variables.h"



void initiateVariables() {


// Define the name of the sensor
SensorName    =  "Sensor-0";



// Configuration parameters that are stored in the SPIFFS /config.json file are:
//
// lastPumpDuration, maxPumpTime, minTimePumpOff, AirValue, WaterValue,
// waterLevelMax, humidityMinPct, irrigateVolume

// MQTT parameters
mqttName      =  "Auto Irrigation Sensor 0";
stateTopic    =  "Irrigation/Sensor-0";
measBaseTopic =  "Irrigation/"+SensorName+"/measVal";
confBaseTopic =  "Irrigation/"+SensorName+"/confVal";

// Define the mqtt configuration parameters
confTopic     =  "Irrigation/Sensor-0/configuration";
cmdTopic      =  "Irrigation/Sensor-0/cmd";

// Other variables below
counter      =  0;

// Define water pump paramters
lastPumpDuration  = 0;        // Time in sec the last time the pump was turned on
maxPumpTime       = 3;        // Maximum allowed pump on time - 3 sec
minTimePumpOff    = 60;       // One minute at least between pump cycles
lastPumpTimeOnTic = millis();
lastPumpTimeOffTic= millis();
PumpOnCmd         = false;
  
// Define the capacative soil moisture sensor input and constants
AirValue           =  1024;   // For calibration in air
WaterValue         =  536;    // For calibration in water

// Define calculation configuration parameters
measHumidity        = true;
measWaterLevel      = true;

// Define water level configuration
waterLevelMax      = 20.0; // Maximum depth to water leve to allow pump                                 // and give alert
waterAlert          = false;
irrigateVolume       = 200;  // The water volume in ml to irrigate

// Define flower humidity configuration
humidityMinPct     = 35; // Minimum allowew humidity reading before water

configurationIsSaved= false; // Boolean that is set true if configuration is saved
waterFlow          = 20; // The water pump flow in ml/sec

}
