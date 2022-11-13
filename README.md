# MQTT Auto Irrigation project for NodeMCU

This project aim to help me and others with their setup of an MQTT connected automatic irrigation system based on NodeMCU.

In order for you to follow this project you must setup the Hardware first.

## Hardware
The hardware chosen for this project can be adapted to your need. This section just lists the needed hardware to duplicate this project.

Here is the list of all hardware items used to setup the auto-irrigation setup you can se in the video and pictures.

| Hardware item #                | Description                                          |
| ------------------------------ | -----------------------------------------------------|
| NodeMCU V3-modul with WIFI     | The brain in the project. You can chose other boards.|
| Capacitive soil moist sensor   | Make sure to buy one that is according to specs!     |
| HC-SR04 Ultrasonic sensor      | This sensor is used to measure the water level.      |
| 5V relay                       | Used to controll the water pump.                     |
| 5V mini water pump             | The pumps that are submersable is used.              |
| Div. electrical components     | Components for assably of the finished board.        |


## Checklist to complete for version 0.1
Things to complete before we call this project version 0.1:
- [x] Create a ReadMe file (this file) to explain the project and steps in it
- [ ] Explain HW setup base NodeMCU in ReadMe file
- [ ] Explain humidity soil sensor integration
- [ ] Explain sonar sensor HW for distance / water level detection
- [ ] Explain HW for pump
- [ ] First code base with setup of the WIFI connection
- [ ] First code base for humidity sensor
- [ ] First code base for distance / water level sensor
- [ ] First code base for pump HW
- [ ] Add configuration for MQTT messages
- [ ] Add new settings in MQTT for: deactivate system, activate system, time to pump before stop and measure, level for humidity, calibration constant for distance
- [ ] Add new messages for monitoring the system: pump on/off, last pump duration, soil humidity
- [ ] Explain the setup

## Setup of your device
TBD
