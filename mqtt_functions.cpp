#include "mqtt_functions.h"

/*
  Function: The callback function for mqtt

  This function is called upon each time data is received from the
  broker. Its used in this context to differentiate between the different 
  subscribed topics.
*/
void callback(char* topic, byte* payload, unsigned int length) {

  String jsonString = "";
  String topicString = String(topic);

  Serial.print("Message received in topic: ");
  Serial.print(topic);
  Serial.print("   length is:");
  Serial.println(length);

  Serial.print("Data Received From Broker:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    jsonString.concat((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");
  Serial.println(jsonString);
  Serial.println(topicString);
  Serial.println(confTopic);
  Serial.println(cmdTopic);
  if (topicString == confTopic) {
    parseConfMessage(jsonString);
    Serial.println("parseConfMessage");
  }
  if (topicString == cmdTopic) {
    parseCmdMessage(jsonString);
    Serial.println("parseCmdMessage");
  }
}




/*
  Function: parseConfMessage

  Input: topicName - the name of the topic to subscribe for
  
  The function subscribes to MQTT topics.
*/
void parseConfMessage(String jsonString) {
  
  // Allocate size on the heap
  DynamicJsonDocument doc(1024);

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, jsonString);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  // Ex. {"AirValue": 1024, "WaterValue": 536, "measHumidity": true, 
  //      "measWaterLevel": true, "maxPumpTime": 3, "waterLevelMax": 20.0, 
  //      "humidityMinPct": 35, "minTimePumpOff":60}

  if (doc.containsKey("AirValue")) {
    AirValue       = doc["AirValue"]; configurationIsSaved = false;
    Serial.print("AirValue is now: ");
    Serial.println(AirValue);
  }
  if (doc.containsKey("WaterValue")) {
    WaterValue     = doc["WaterValue"]; configurationIsSaved = false;
    Serial.print("WaterValue is now: ");
    Serial.println(WaterValue);   
  }
  if (doc.containsKey("measHumidity")) {
    measHumidity   = doc["measHumidity"]; configurationIsSaved = false;
    Serial.print("measHumidity is now: ");
    Serial.println(measHumidity);  
  }
  if (doc.containsKey("measWaterLevel")) {
    measWaterLevel = doc["measWaterLevel"]; configurationIsSaved = false;  
    Serial.print("measWaterLevel is now: ");
    Serial.println(measWaterLevel);  
  }
  if (doc.containsKey("maxPumpTime")) {
    maxPumpTime    = doc["maxPumpTime"]; configurationIsSaved = false;
    Serial.print("maxPumpTime is now: ");
    Serial.println(maxPumpTime);      
  }
  if (doc.containsKey("waterLevelMax")) {
    waterLevelMax  = doc["waterLevelMax"]; configurationIsSaved = false;
    Serial.print("waterLevelMax is now: ");
    Serial.println(waterLevelMax);          
  }
  if (doc.containsKey("humidityMinPct")) {
    humidityMinPct = doc["humidityMinPct"]; configurationIsSaved = false;
    Serial.print("humidityMinPct is now: ");
    Serial.println(humidityMinPct);      
  }
  if (doc.containsKey("minTimePumpOff")) {
    minTimePumpOff = doc["minTimePumpOff"]; configurationIsSaved = false;
    Serial.print("minTimePumpOff is now: ");
    Serial.println(minTimePumpOff);      
  }
  if (doc.containsKey("irrigateVolume")) {
    irrigateVolume = doc["irrigateVolume"]; configurationIsSaved = false;
    Serial.print("irrigateVolume is now: ");
    Serial.println(irrigateVolume);      
  }
  if (doc.containsKey("waterFlow")) {
    waterFlow = doc["waterFlow"]; configurationIsSaved = false;
    Serial.print("waterFlow is now: ");
    Serial.println(waterFlow);      
  }
}


/*
  Function: parseCmdMessage

  Input: topicName - the name of the topic to subscribe for
  
  The function subscribes to MQTT topics.
*/
void parseCmdMessage(String jsonString) {
  
  // Allocate size on the heap
  DynamicJsonDocument doc(400);

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, jsonString);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  // Ex. {"PumpOn": false}
  if (doc.containsKey("PumpOn")) {
    PumpOnCmd       = doc["PumpOn"];
  
    // Print values.
    Serial.print("PumpOnCmd is now: ");
    Serial.println(PumpOnCmd);
  
    if (PumpOnCmd) {
      pumpWater(irrigateVolume);      
    } else {   
      turnPumpOff(); // Just make sure pump is turned off
    }
  }
  if (doc.containsKey("SaveConf")) {
    
    saveConfigurationParameters();
    Serial.println("SaveConf received!");
    
  }
}


/*
  Function: publishValues
  
  The function publishes all meas and conf values.
*/
void publishValues() {
  
  publishMeasValues();               // Publish all measured values
  
  publishConfValues();               // Publish all measured values

}


/*
  Function: publishMeasValues

  The function publishes all measured value that exists.
*/
void publishMeasValues() {
  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["counter"]             = counter;
  doc["rssi"]                = rssi;
  doc["soilMoistureValue"]   = humidityPercentage;
  doc["distanceValue"]       = waterLevelCm;
  doc["lastPumpDuration"]    = lastPumpDuration;

  size_t n = serializeJson(doc, buffer);

  bool published = client.publish(measBaseTopic.c_str(), buffer, n);
  if (published) Serial.println("Published all measured values!");

  client.publish((measBaseTopic+"/waterAlert").c_str(), 
                  (bToStr(waterAlert)).c_str(), 2);
  client.publish((measBaseTopic+"/motorState").c_str(), 
                  (bToStr(motorState)).c_str(), 2);

}



/*
  Function: publishConfValues

  The function publishes all configuration value that exists.
*/
void publishConfValues() {
  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["AirValue"]            = AirValue;
  doc["WaterValue"]          = WaterValue;
  doc["humidityMinPct"]      = humidityMinPct;
  doc["measWaterLevel"]      = measWaterLevel;
  doc["maxPumpTime"]         = maxPumpTime;
  doc["minTimePumpOff"]      = minTimePumpOff;
  doc["waterLevelMax"]       = waterLevelMax;
  doc["irrigateVolume"]      = irrigateVolume;
  doc["waterFlow"]           = waterFlow;

  size_t n = serializeJson(doc, buffer);

  bool published = client.publish(confBaseTopic.c_str(), buffer, n);
  if (published) Serial.println("Published all configuration values!");

  client.publish((confBaseTopic+"/configurationIsSaved").c_str(), 
                  (bToStr(configurationIsSaved)).c_str(), 2);

}



/*
  Function: bToStr

  Input: boolean inputBool the boolean to convert

  Outout: const char* of the boolean

  The function converts a boolean and output a c_str const char pointer.
*/
String bToStr(bool inputBool) {
  String tString = "true";
  String fString = "false";
  if (inputBool) {
    return tString;
  } else {
    return fString;
  }
}


/*
  Function: sendAvailabilityDiscoveryMsg

  The function send MQTT Discovery availability message.
*/
void sendAvailabilityDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/availability/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["state_topic"]           = willTopic;
  doc["name"]                  = "Irrigation_Sensor0_Availability";
  doc["unique_id"]             = "Irrigation0-Availability";
  
  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);  
}



/*
  Function: sendDistanceDiscoveryMsg

  The function send MQTT Discovery message for distance parameter.
*/
void sendDistanceDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/distance/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.distanceValue }}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_Distance";
  doc["unique_id"]             = "Irrigation0-Distance";
  
  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}



/*
  Function: sendHumidityDiscoveryMsg

  The function send MQTT Discovery message for humidity parameter.
*/
void sendHumidityDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/soil-humidity/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.soilMoistureValue }}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_Soil_Humidity";
  doc["unique_id"]             = "Irrigation0-SOILHUMIDITY";


  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}


/*
  Function: sendRssiDiscoveryMsg

  The function send MQTT Discovery message for RSSI parameter.
*/
void sendRssiDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/rssi/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.rssi }}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_rssi";
  doc["unique_id"]             = "Irrigation0-rssi";


  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}


/*
  Function: sendCounterDiscoveryMsg

  The function send MQTT Discovery message for Counter parameter.
*/
void sendCounterDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/counter/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.counter }}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_counter";
  doc["unique_id"]             = "Irrigation0-counter";


  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}


/*
  Function: sendMotorstateDiscoveryMsg

  The function send MQTT Discovery message for the motor state.
*/
void sendMotorstateDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/motorstate/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.motorState }}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_motorState";
  doc["unique_id"]             = "Irrigation0-motorState";


  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}


/*
  Function: sendlastPumpDurationDiscoveryMsg

  The function send MQTT Discovery message for the lastPumpDuration.
*/
void sendlastPumpDurationDiscoveryMsg() {
  String discoveryTopic = "homeassistant/sensor/irrigation-sensor0/lastPumpDuration/config";

  DynamicJsonDocument doc(1024);
  char buffer[512];

  doc["value_template"]        = "{{ value_json.lastPumpDuration}}";
  doc["state_topic"]           = stateTopic;
  doc["json_attributes_topic"] = stateTopic;
  doc["name"]                  = "Irrigation_Sensor0_lastPumpDuration";
  doc["unique_id"]             = "Irrigation0-lastPumpDuration";


  size_t n = serializeJson(doc, buffer);

  client.publish(discoveryTopic.c_str(), buffer, n);
}
