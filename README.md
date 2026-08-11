# Time-Stamped Sensor Data Logger using LPC2148

## Project Overview

This project implements a Time-Stamped Sensor Data Logger using the LPC2148 ARM7 microcontroller. The system continuously monitors temperature using the LM35 sensor, records measurements with real-time RTC timestamps, displays live data on a 16×2 LCD, and transmits the logged information through UART for monitoring 
and analysis.

## Objective

The objective of this project is to develop a **Time-Stamped Temperature Data Logger using the LPC2148 microcontroller** to continuously monitor temperature using an **LM35 sensor** and acquire the sensor data through the **ADC**. The system records and displays the temperature along with accurate **date and time information from the built-in RTC** on a **16×2 LCD** and transmits the timestamped temperature data to a PC through **UART** for logging and analysis. It also provides **temperature threshold monitoring and over-temperature alerts** when the temperature exceeds the predefined set point. A **keypad interface** is provided to allow the user to edit the **RTC date/time and temperature set point**, making the system suitable for reliable real-time temperature monitoring and data logging applications.

## Features

* **Real-Time Temperature Monitoring** – Continuously measures temperature using the LM35 sensor through the LPC2148 ADC.

* **RTC-Based Time Stamping** – Records each temperature reading along with accurate date and time information using the LPC2148 built-in RTC.

* **16×2 LCD Display** – Displays real-time temperature, date, time, and day information for easy monitoring.

* **UART Data Logging** – Transmits timestamped temperature readings to a PC or serial terminal through UART for logging and analysis.

* **Temperature Set-Point Monitoring** – Compares the measured temperature with a user-defined temperature threshold.

* **Over-Temperature Alert** – Activates an LED/buzzer and provides an alert through the serial terminal when the temperature exceeds the configured set point.

* **RTC Editing** – Allows the user to update the hour, minute, second, date, month, year, and day through the keypad.

* **Temperature Set-Point Editing** – Allows the user to modify the temperature threshold using the keypad.

* **Keypad-Based User Interface** – Provides a simple menu-based interface for configuring RTC parameters and the temperature set point.

* **Input Validation** – Ensures that the entered RTC values are within their permitted ranges.

* **Continuous Monitoring and Logging** – Continuously monitors temperature, maintains accurate time stamping, and transmits data for reliable tracking and analysis.


## Hardware Requirements

* **LPC2148 ARM7 Microcontroller**
* **LM35 Temperature Sensor**
* **16×2 LCD Display**
* **Matrix Keypad**
* **Push Button / Switch**
* **LED / Buzzer**
* **MAX232 Serial Communication Interface**

## Software Requirements

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
