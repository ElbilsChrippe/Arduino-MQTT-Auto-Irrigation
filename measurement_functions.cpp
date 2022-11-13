#include "measurement_functions.h"

/*
  Function: measureValues
  
  The function measures all measurement values.
*/
void measureValues() {

  updateCounter();                   // Update the cycle counter

  measureRssi();                     // Measure RSSI on wifi

  measureWaterLevel(measWaterLevel); // Measure water level

  measureHumidity(measHumidity);     // Measure humidity in soil

  checkWaterLevel();                 // Check the water level
  
}


/*
  Function: updateCounter

  The function updates the counter value.
*/
void updateCounter() {
  // Increase the alive counter
  counter = counter + 1;
  Serial.print("This cycle is : ");
  Serial.print(counter);
  Serial.println();
  
}


/*
  Function: checkWaterLevel

  The function checks that the water level in container is ok, if not the 
  water alert is set.
*/
void checkWaterLevel() {
  if (waterLevelCm >= waterLevelMax) {
    waterAlert = true;
  } else {
    waterAlert = false;
  }
}


/*
  Function: measureRssi

  Output: rssi - the RSSI value
  
  The function measures the RSSI strength.
*/
int32_t measureRssi() {
  // Get the WiFi strength
  rssi = WiFi.RSSI();
  Serial.print("RSSI is: ");
  Serial.println(rssi);

  return rssi;
}



/*
  Function: measureHumidity

  Input: doMeasurement - boolean if measurement shall be done
 
  The function measures the hunidity level in percentage within the soil.
*/
void measureHumidity(bool doMeasurement) {

  if (doMeasurement = false)  {
    humidityPercentage = 100;
    return;
  }
  
  int soilMoistureValue    =  0;
  float soilmoisturepercent  =  0.0;  

  // Read out soil humidity sensor value
  soilMoistureValue = analogRead(A0);

  
  if (soilMoistureValue > AirValue) {
    soilMoistureValue = AirValue;
  }
  if (soilMoistureValue < WaterValue) {
    soilMoistureValue = WaterValue;
  }
  
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  Serial.print("Soli sensor moisture percentage: ");
  Serial.println(soilmoisturepercent);

  humidityPercentage = soilmoisturepercent;
  
}



/*
  Function: measureWaterLevel

  Input: doMeasurement - boolean if measurement shall be done
 
  The function measures the distance to the water level.
*/
void measureWaterLevel(bool doMeasurement) {

  if (doMeasurement = false) {
    waterLevelCm = 100;
    return;
  }

  long duration;
  float distanceCm;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  waterLevelCm = distanceCm;
}
