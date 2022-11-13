/*
  Mqtt Auto Irrigation

  Turns on WiFi and hooks up to mqtt and post a counter and RSSI.

  Used to hook up into Home Assistant and monitor if Monika is ready to go or has come home.

*/

#include "global_variables.h"
#include "pump_functions.h"
#include "measurement_functions.h"
#include "mqtt_functions.h"


/*
  Function: setup

  The setup function runs once when you press reset or power the board.
*/
void setup() {

  initiateVariables();
  
  Serial.begin(115200);
  Serial.println("mounting FS...");
 
  if (SPIFFS.begin()) {
    delay(100);
    Serial.println("Mounted file system");
    if (!SPIFFS.exists("/config.json")) {
      delay(100);
      Serial.println("File /config.json does not exist! Creating this file.");
      File file = SPIFFS.open("/config.json", "w");
      file.close();
      if (saveConfigurationParameters() == false) {
        Serial.println("Unable to save configuration paramters");
      }
    }
    configurationIsSaved = true;
  }

  delay(3000); // Wait 3 seconds for file operations
    
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    yield();
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(broker, port);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(mqttName.c_str(), mqttUser, mqttPass, willTopic, willQoS, willRetain, willMessage))
    {

      Serial.println("connected to MQTT broker");

      sendAvailabilityDiscoveryMsg();
      sendCounterDiscoveryMsg();
      sendRssiDiscoveryMsg();
      sendDistanceDiscoveryMsg();
      sendHumidityDiscoveryMsg();
      sendMotorstateDiscoveryMsg();
      sendlastPumpDurationDiscoveryMsg();
      client.publish(willTopic, "online");

    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(500);

    }
  }
  
  Serial.println("ESP8266 AS SUBSCRIBER");
  Serial.print("Subscribing topic: ");
  Serial.println(confTopic);
  client.subscribe(confTopic.c_str());
  Serial.print("Subscribing topic: ");
  Serial.println(cmdTopic);
  client.subscribe(cmdTopic.c_str());

  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the water motor pump relay
  pinMode(motorPin, OUTPUT);
  motorState = false;
  digitalWrite(motorPin, LOW); // keep motor off initally

  // Initialize the ultrasonic water level sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output for ultrasonic sensor
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input for ultrasonic sensor

  // Read in old configration parameters from SPIFFS /config.json file
  if (readConfigurationParameters() == false) {
    Serial.println("Unable to read config.json file and restore values!!");
  }
}


/*
  Function: main loop function

  This is the main loop function.
*/
void loop() {
  client.loop();

  measureValues();
  publishValues();
  delay(2000);

}
