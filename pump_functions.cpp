#include "pump_functions.h"

/*
  Function: pumpWater

  Input: waterVolume - float

  The function turns on the water pump in steps of MaxPumpTime and waits for
  MinTimePumpOff and repeats untill water Volume is meet.
*/
void pumpWater(float waterVolume) {
  Serial.print("Starting to Irrigate the plant with volume: "); Serial.print(waterVolume);
  Serial.println(" ml.");

  float waterVolumePerBurst = waterFlow * maxPumpTime;
  Serial.print("waterVolumePerBurst : "); Serial.print(waterVolumePerBurst);
  Serial.println("");
  int nrOfBursts = floor(waterVolume / waterVolumePerBurst);
  Serial.print("Will irrigate "); Serial.print(nrOfBursts);
  Serial.println(" times!");
  
  if (!checkPumpConditions(humidityPercentage, waterLevelCm)) { // Check the conditions
    Serial.println("Pump not turned on since condition not meet!");
    return;
  }

  uint64_t timeStart = millis();
  uint64_t timePump = timeStart;

  while ((millis() - timeStart) < minTimePumpOff*1000*(nrOfBursts+1)) {
    motorState = true;
    // Check if time ahas passed for one pump cycle
    // the delay function in measureAndPublish needs to be added ( ~3000 ms)
    if ((millis()- timePump) + 3000 > minTimePumpOff*1000) { 
      timePump = millis();
      Serial.print("timePump is :  "); Serial.print(timePump); Serial.println("");
      if (checkPumpConditions(0, waterLevelCm)) { // Only check water
        turnPumpOn();
      } else {
        Serial.println("Pump conditions not meet");
      }
    }
    measureValues();
    publishValues();
    delay(2000);

    Serial.println("In pumpWater function");
  }
  Serial.println("Irrigation cycle finished");
  motorState = false;

}


/*
  Function: checkPumpConditions

  Input: 
          humidity, the humidity level in percentage
          waterLevel, current measured water Level

  Output: boolean, true if humidity conditions are okay to run pump 

  The function checks if conditions are meet for running the pump.
  The conditions are:
   - Time since last pump action is > minTimePumpOff
   - Humidity level is low enough (Humidity < humidityMinPct)
   - Water Level is meet (level > waterLevelMax)
*/
bool checkPumpConditions(float humidity, float waterLevel) {
  bool conditionsMeet = false;

  // Conditions: humdity < min config value
  //             water level > max config value
  //             time since last pump off > minimum config time
  if (humidity < humidityMinPct) {
    Serial.println("humidity < humidityMinPct");
    if (waterLevel < waterLevelMax) {
      Serial.println("waterLevel < waterLevelMax");
      Serial.print("time duration: ");Serial.print((millis() + 100 - lastPumpTimeOffTic));
      Serial.println("");
      Serial.print("minTimePumpOff*1000: ");Serial.print(minTimePumpOff*1000);
      Serial.println("");
      if ((millis() + 100 - lastPumpTimeOffTic) > minTimePumpOff*1000) {
        Serial.println("time cond meet");
        conditionsMeet = true;
      }
    }
  }

  return conditionsMeet;
}


/*
  Function: turnPumpOn

  The function turns on the water pump. The function automatically turns off
  the pump after the max pump time.
*/
void turnPumpOn() {

  Serial.println("Turning on pump!");
  digitalWrite(motorPin, HIGH);
  lastPumpTimeOnTic = millis();
  while ((millis()-lastPumpTimeOnTic) < maxPumpTime*1000) {
    // Let the pump work for maxPumpTime milliseconds
    delay(100);
    Serial.print("Current duration :"); Serial.print((millis()-lastPumpTimeOnTic));
    Serial.println(" ..");
  }
  turnPumpOff(); // Turn off pump!!
}


/*
  Function: turnPumpOff

  The function turns off the water pump.
*/
void turnPumpOff() {
  
  digitalWrite(motorPin, LOW);
  lastPumpTimeOffTic = millis();
  lastPumpDuration = millis() - lastPumpTimeOnTic;
  
}
