#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>


// ####### CONFIGURATION PARAMETERS - START ############

// Define the WIFI login credentials
inline const char *ssid          =  "ssid-name";
inline const char *password      =  "wifi-password";

// Define the mqtt variables
inline const char *broker        =  "x.x.x.x";
inline const int   port =  1883;
inline const char *mqttUser      =  "mosquitto";
inline const char *mqttPass      =  "password";

// Define the motor relay control
inline const int   motorPin     =  D0;
// Define the ultrasonic sensor settings
inline const int   trigPin      =  D2;
inline const int   echoPin      =  D3;

// Define the name of the sensor
inline String      SensorName;

// ####### CONFIGURATION PARAMETERS - END ############


// Configuration parameters that are stored in the SPIFFS /config.json file are:
//
// lastPumpDuration, maxPumpTime, minTimePumpOff, AirValue, WaterValue,
// waterLevelMax, humidityMinPct, irrigateVolume

// MQTT parameters
inline const char *willTopic     =  "Irrigation/Sensor-0/availability";
inline const int   willQoS       =  1;
inline const bool  willRetain    =  true;
inline const char *willMessage   =  "offline";
inline String      mqttName;
inline String      stateTopic;
inline String      measBaseTopic;
inline String      confBaseTopic;

// Define the mqtt configuration parameters
inline String      confTopic;
inline String      cmdTopic;

// Other variables below
inline uint64_t    counter;
inline bool        motorState;

// Define water pump paramters
inline uint64_t    lastPumpDuration;        // Time in sec the last time the pump was turned on
inline uint64_t    maxPumpTime;        // Maximum allowed pump on time - 3 sec
inline uint64_t    minTimePumpOff;       // One minute at least between pump cycles
inline uint64_t    lastPumpTimeOnTic;
inline uint64_t    lastPumpTimeOffTic;
inline bool        PumpOnCmd;
  
// Define the capacative soil moisture sensor input and constants
inline int   AirValue;   // For calibration in air
inline int   WaterValue;    // For calibration in water
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

// Define calculation configuration parameters
inline bool measHumidity;
inline bool measWaterLevel;

// Define water level configuration
inline float waterLevelMax; // Maximum depth to water leve to allow pump                                 // and give alert
inline bool waterAlert;
inline int irrigateVolume;  // The water volume in ml to irrigate

// Define flower humidity configuration
inline float humidityMinPct; // Minimum allowew humidity reading before water

inline float waterLevelCm;
inline float humidityPercentage;

inline bool configurationIsSaved; // Boolean that is set true if configuration is saved
inline float waterFlow; // The water pump flow in ml/sec

inline int32_t     rssi;


inline WiFiClient espClient;
inline PubSubClient client(espClient);

void initiateVariables();

#endif
