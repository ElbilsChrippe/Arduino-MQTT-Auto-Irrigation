#include "config_functions.h"




/*
  Function: readConfigurationParameters

  Output: boolean, true if successfull and false if not

  The function reads all the configuration parameter from stored SPIFFS file.
*/
bool readConfigurationParameters() {
  //read configuration from FS json
  Serial.println("mounting FS...");
 
  if (SPIFFS.begin()) {
    Serial.println("Mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("Reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      
      if (configFile) {
        Serial.println("Opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, buf.get());
        
        // Test if parsing succeeds.
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return false;
        }
        
        Serial.println("Parsed json");
        // lastPumpDuration, maxPumpTime, minTimePumpOff, AirValue, WaterValue,
        // waterLevelMax, humidityMinPct, irrigateVolume
        if (doc.containsKey("lastPumpDuration")) { 
          lastPumpDuration = doc["lastPumpDuration"]; 
        }
        if (doc.containsKey("maxPumpTime")) { 
          maxPumpTime = doc["maxPumpTime"]; 
        }
        if (doc.containsKey("minTimePumpOff")) { 
          minTimePumpOff = doc["minTimePumpOff"]; 
        }
        if (doc.containsKey("AirValue")) { 
          AirValue = doc["AirValue"]; 
        }
        if (doc.containsKey("WaterValue")) { 
          WaterValue = doc["WaterValue"]; 
        }
        if (doc.containsKey("waterLevelMax")) { 
          waterLevelMax = doc["waterLevelMax"]; 
        }
        if (doc.containsKey("humidityMinPct")) { 
          humidityMinPct = doc["humidityMinPct"]; 
        }
        if (doc.containsKey("irrigateVolume")) { 
          irrigateVolume = doc["irrigateVolume"]; 
        }
      }
    } else {
      Serial.println("File /config.json does not exist!");
      return false;
    }
  } else {
    Serial.println("failed to mount FS");
    return false;
  }

  return true;
}



/*
  Function: saveConfigurationParameters

  Output: boolean, true if successfull and false if not

  The function saves all the configuration parameter to SPIFFS config.json file.
*/
bool saveConfigurationParameters() {
    
  Serial.println("Saving configuration variables to SPIFFS json file");

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, configFile);

  char buffer[512];
  // lastPumpDuration, maxPumpTime, minTimePumpOff, AirValue, WaterValue,
  // waterLevelMax, humidityMinPct, irrigateVolume
        
  doc["lastPumpDuration"]   = lastPumpDuration;
  doc["maxPumpTime"]        = maxPumpTime;
  doc["minTimePumpOff"]     = minTimePumpOff;
  doc["AirValue"]           = AirValue;
  doc["WaterValue"]         = WaterValue;
  doc["waterLevelMax"]      = waterLevelMax;
  doc["humidityMinPct"]     = humidityMinPct;
  doc["irrigateVolume"]     = irrigateVolume;
  
  size_t n = serializeJson(doc, buffer);
  
  configFile.close();

  configFile = SPIFFS.open("/config.json", "w");
  serializeJson(doc, configFile);
  serializeJson(doc, buffer);
  configFile.close();
  Serial.println("");
  Serial.println("File config.json saved - OK.");

  configurationIsSaved = true;

  return true;
  
}
