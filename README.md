# MQTT Auto Irrigation project for NodeMCU

This project aim to help me and others with their setup of an MQTT connected automatic irrigation system based on NodeMCU.

The need that this project solves is to be able through MQTT command the irrigation platform to initiate plant irrigation based on humidity level in the soil. The commands and configuration is sent to the device through MQTT so that you can controll it from e.g. Home Assistant. The project is having safeguard of the water level and also the set humidity level.

In order for you to follow this project you must setup the Hardware first.

## Hardware
The hardware chosen for this project can be adapted to your need. This section just lists the needed hardware to duplicate this project.

Here is the list of all hardware items used to setup the auto-irrigation setup you can se in the video and pictures.

| Hardware item #                | Description                                          | Links to similar products          |
| ------------------------------ | -----------------------------------------------------|------------------------------------|
| NodeMCU V3-modul with WIFI     | The brain in the project. You can chose other boards.|[link on Amazon](https://a.co/d/9oF6tCM)
| Capacitive soil moist sensor   | Make sure to buy one that is according to specs!     |[link on Amazon](https://a.co/d/hjZC2gR)
| HC-SR04 Ultrasonic sensor      | This sensor is used to measure the water level.      |[link on Amazone](https://a.co/d/eIeM4bu)
| 5V relay                       | Used to controll the water pump.                     |[link on Amazon](https://a.co/d/5dMYgE1)
| 5V mini water pump             | The pumps that are submersable is used.              |[link on Amazon](https://a.co/d/bT1MYee)
| Div. electrical components     | Components for assably of the finished board.        |

In addition to this ou also need a 5V power suply for the NodeMCU but it is also possible to power this device with a battery solution.

## Checklist to complete for version 0.1
Things to complete before we call this project version 0.1:
- [x] Create a ReadMe file (this file) to explain the project and steps in it
- [x] Explain HW setup base NodeMCU in ReadMe file
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
To setup this project lets start with the humidity soil sensor integration.
