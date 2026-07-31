/*
===============================================================================
File Name   : lm35.c
Description :
This file contains functions for interfacing the LM35
temperature sensor with LPC21xx microcontroller.

It provides:
- Reading temperature in Celsius or Fahrenheit
- Reading normal LM35 temperature values
- Reading non-precision/differential temperature values

The LM35 sensor output is read using ADC channels.
===============================================================================
*/

#include "types.h"         // Custom data type definitions
#include "adc.h"           // ADC function declarations
#include "adc_defines.h"   // ADC channel definitions


/********************************************************
 Old implementation for direct Celsius and Fahrenheit
 calculation using pointer arguments.
********************************************************/

/*

===============================================================================
Function Name : Read_LM35
Description   :
Reads temperature from LM35 sensor using ADC channel 1
and returns temperature either in Celsius or Fahrenheit.

Parameter     :
tType -> 'C' for Celsius
          'F' for Fahrenheit

Return Value  :
Temperature value
===============================================================================
*/
u32 Read_LM35(u8 tType)

{

	u32 adcDVal; f32 eAR;
	u32 tDeg;

	// Read ADC value from channel 1
	Read_ADC(CH1,&eAR,&adcDVal);

	// Convert voltage to Celsius
	tDeg=(int)(eAR * 100);

	if(tType=='C');
		// Temperature already in Celsius

	else if(tType=='F')

		// Convert Celsius to Fahrenheit
		tDeg=((eAR * (9/5.0))+32);

	return tDeg;

}


/*
===============================================================================
Function Name : Read_LM35_NP
Description   :
Reads temperature difference using ADC channel 0 and 1.
Can return temperature in Celsius or Fahrenheit.

Parameter     :
tType -> 'C' for Celsius
          'F' for Fahrenheit

Return Value  :
Temperature value
===============================================================================
*/
f32 Read_LM35_NP(u8 tType)

{

	u32 adcDVal1,adcDVal2; 

	f32 eAR1,eAR2,tDeg;

	// Read ADC values from channel 0 and channel 1
	Read_ADC(CH0,&eAR1,&adcDVal1);

	Read_ADC(CH1,&eAR2,&adcDVal2);

	// Calculate temperature difference
	tDeg=(eAR1-eAR2) * 100;

	if(tType=='C');

		// Temperature already in Celsius

	else if(tType=='F')

		// Convert Celsius to Fahrenheit
		tDeg=((tDeg * (9/5.0))+32);

	return tDeg;

}

