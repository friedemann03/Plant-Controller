# Plant Watering System

This is my final project for the Making Embedded Systems Course by Elecia White (Yellow Seahorses Cohort in 2022).

## Basic Description
The Watering System is used to keep plants alive by monitoring and watering them when needed.
The system can run in two different trigger modes, time based watering and moisture based watering.
In the first one, you can set an interval after which the plant gets watered and in the second mode
the system uses its soil moisture sensor to decide when to water. The system obviously will not water
during the night.

For the watering itself, the system uses a small tank and a peristaltic pump. The water level in the tank is monitored
by a ultrasonic distance sensor, meaning the system is dependent on knowing the tank size.
Watering happens either by using the moisture sensor's feedback or by a set amount of water.

The system also displays information on an LCD Screen. 
You can cycle through Moisture Level, Water Level, Current Time, Current Watering and Trigger Mode by pressing a button.

Changing the watering mode, the trigger mode, setting times and moisture levels etc. is done via a simple terminal over UART.