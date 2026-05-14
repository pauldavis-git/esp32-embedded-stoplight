

# esp32-embedded-stoplight
An embedded C++/Arduino project using an ESP32 microcontroller to simulate a stoplight and crosswalk.

## Video
https://www.youtube.com/shorts/EiKcDvJLNV0

## Description
The program begins with the green light in a stoplight illuminated. Upon a button press, simulating a pedestrian arriving at a crosswalk, the stoplight will change to yellow, and then red. Once red, the pedestrian "X" will turn to a countdown from 9, simulating the pedestrian being allowed to cross. As the timer runs out, and audible beep will sound until the timer reaches 0, in which case it will change back to a red "X", and the stoplight will cycle back to green.

## Features
- LED light cycling oon push button input
- Button Debounce handling to detect differentiate real and faulty input
- Full utilization of 7 segment display and audible buzzer

## Hardware
- ESP32 Dev Board
- Breadboard
- LEDs(Red, Yellow, and Green)
- Push Button
- 220 Ohm Resistors
- Wires

## Pin Configuration
- Stoplights: {red: 13, yellow: 12, green: 14}
- Button: 27
- Buzzer: 15
- 7 segment {22, 3, 1, 23, 21, 19, 18}

## Structure
Currently, the program source is stoplight.io.


