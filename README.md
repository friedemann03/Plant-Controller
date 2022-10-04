# Plant Watering System

This is my final project for the Making Embedded Systems Course by Elecia White (Yellow Seahorses Cohort in 2022).

## Basic Description
The watering system is used to water plants at home. When active, it checks the soil moisture around the plant.
If the moisture level is below a preset value it will water the plant until the soil is moist again.
When inactive for a while, it will go to sleep. Every 10 minutes it wakes up and checks for the soil moisture, the water level of the tank and 
then goes back to sleep again. The user has two ways to interact with the system. First, by pressing a button the system gets active
and displays information on an LCD screen which you can cycle through by pressing the button again. Second, by interfacing to it with a UART Terminal, that is used
for debugging and setting the moisture level at which the system should water the plant.

For the watering itself, the system uses a small tank and a peristaltic pump. The water level in the tank is monitored
by an ultrasonic distance sensor, meaning the system is dependent on knowing the tank size. If the tank is empty, the system
will notify the user by blinking an LED and displaying a warning message on the LCD screen.

The system also makes predictions about when the next watering is likely to occur, based on previous times, how much water is needed on average and how long the remaining water in the tank will last.
This information is also available on the LCD Screen by cycling through it with the button or by requesting them over the UART Terminal.
It can be used to calculate how much water the plant will probably need if you go on vacation.

A full state machine of the system: ![State Machine](docs/images/StateMachine_PlantController.png)
The state machine can also be found [here](https://docs.google.com/spreadsheets/d/1Z40RKTnW3gGIQifepFi1jO9dVKSzbtFp8474BN1ClBw/edit?usp=sharing).
