# Time-Stamped Sensor Data Logger using LPC2148

## Project Overview

This project implements a Time-Stamped Sensor Data Logger using the LPC2148 ARM7 microcontroller. The system continuously monitors temperature using the LM35 sensor, records measurements with real-time RTC timestamps, displays live data on a 16×2 LCD, and transmits the logged information through UART for monitoring and analysis.

## Features

- Real-time temperature monitoring using LM35
- RTC-based date and time stamping
- UART serial communication
- 16×2 LCD display
- Keypad-based RTC and set-point configuration
- Configurable temperature threshold
- Over-temperature indication using LED/Buzzer
- Modular Embedded C implementation

## Hardware

- LPC2148 ARM7 Microcontroller
- LM35 Temperature Sensor
- 16×2 LCD
- Matrix Keypad
- MAX232
- LED/Buzzer

## Software

- Embedded C
- Keil uVision
- Flash Magic

## Project Modules

- ADC
- UART
- RTC
- LCD
- Keypad
- Temperature Display
- RTC Editing
- Set-Point Editing
