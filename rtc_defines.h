/*
===============================================================================
File Name   : rtc_defines.h
Description :
This header file contains macro definitions required for configuring the 
Real Time Clock (RTC) module.

It defines:
- System oscillator frequency
- CPU clock (CCLK)
- Peripheral clock (PCLK)
- RTC prescaler calculation values
- Control register (CCR) bit definitions

These macros are used during RTC initialization and configuration to 
generate accurate 1-second timing from the system clock.
===============================================================================
*/

#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H

// System clock and peripheral clock Macros

#define FOSC 12000000        // Main oscillator frequency (12 MHz)

#define CCLK (5*FOSC)        // CPU Clock = 5 × Oscillator frequency

#define PCLK (CCLK/4)        // Peripheral Clock = CPU Clock / 4


// RTC Macros

// Prescaler integer value calculation for generating 1 Hz RTC clock
#define PREINT_VAL ((PCLK/32768)-1)

// Prescaler fractional value calculation for accurate timing
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)


// CCR (Clock Control Register) register bits 

#define RTC_ENABLE  (1<<0)   // Enable RTC (bit 0)

#define RTC_RESET   (1<<1)   // Reset RTC (bit 1)

#define RTC_CLKSRC  (1<<4)   // Select clock source for RTC (bit 4)


//#define _LPC2148      // Uncomment if using LPC2148 (conditional compilation)

#endif
