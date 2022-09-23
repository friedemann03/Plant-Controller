# MES: Exercise Week 4 

## Task
> Start putting together a plan for your final project. Given the chapter, the main goal is to put
> together state machine documentation. This can be a flowchart or (preferably) a state table.
> You may also need to (re)create the diagrams from Chapter Two: System Architecture to flesh
> out the design.

## Basic Overview over System

### System States

1. Normal State:
    - gathering moisture data
    - console / terminal app running
    - update LCD Screen and react to button presses
    - update water level by gathering sensor data
    - slow blinking led
    - check for transitioning
2. Watering State:
    - water the plant
    - display warning on LCD Screen, not updating or responding anymore
    - disable terminal/console app
    - fast blinking led
    - gathering moisture and water level data (needed for watering)

When System is finished with watering, it will return to normal state, which it is in most of the time.

## State Machines in the System

### Check for Transitioning form normal to watering state
| State            | yes            | no                |
|------------------|----------------|-------------------|
| IS_NIGHTTIME     | NOT_WATERING   | IS_MODE_TIME      |
| IS_MODE_TIME     | IS_TIME_PASSED | IS_MODE_MOISTURE  |
| IS_MODE_MOISTURE | NEEDS_WATER    | NOT_WATERING      |
| IS_TIME_PASSED   | START_WATERING | NOT_WATERING      |
| NEEDS_WATER      | START_WATERING | NOT_WATERING      |
| START_WATERING   | finished       | finished          |
| NOT_WATERING     | finished       | finished          |


