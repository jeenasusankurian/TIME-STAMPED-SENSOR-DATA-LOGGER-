/*
===============================================================================
File Name   : adc.c
Description :
This file contains functions related to ADC (Analog to Digital Converter)
operation in LPC21xx microcontroller.

It provides:
- ADC channel initialization
- ADC data conversion and reading
- Analog voltage calculation from digital value

Supported ADC channels:
AIN0 (P0.27) to AIN3 (P0.30)
===============================================================================
*/

#include "types.h"        // Custom data type definitions
#include "delay.h"        // Delay function declarations
#include <LPC21xx.h>      // LPC21xx register definitions
#include "adc_defines.h"  // ADC related macro definitions


// ADC channel selection lookup table
u32 adcChSel[4]={AIN0_PIN_0_27,

                 AIN1_PIN_0_28,

                 AIN2_PIN_0_29,

                 AIN3_PIN_0_30

                };


/*
===============================================================================
Function Name : Init_ADC
Description   :
Initializes the required ADC channel and configures
the ADC control register.

Parameter     :
chNo -> ADC channel number (0 to 3)

Return Value  :
None
===============================================================================
*/
void Init_ADC(u32 chNo)

{

	// Clear previous pin configuration
	PINSEL1&=~(adcChSel[chNo]);

	// Configure selected pin as ADC input
	PINSEL1|=adcChSel[chNo];

	// Enable ADC and set clock divider
	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);

}


/*
===============================================================================
Function Name : Read_ADC
Description   :
Starts ADC conversion, waits for completion,
reads digital value, and calculates equivalent voltage.

Parameter     :
chNo    -> ADC channel number
eAR     -> Pointer to store analog voltage
adcDVal -> Pointer to store digital ADC value

Return Value  :
None
===============================================================================
*/
void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal)

{

	// Clear previous channel selection
	ADCR&=0xFFFFFF00;

	// Select required channel and start conversion
	ADCR|=((1<<ADC_CONV_START_BIT)|(1<<chNo));

	// Small delay for conversion
	delay_us(3);

	// Wait until conversion completes
	while(((ADDR>>DONE_BIT)&1)==0);

	// Stop ADC conversion
	ADCR&=~(1<<ADC_CONV_START_BIT);

	// Read 10-bit digital ADC value
	*adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);

	// Calculate equivalent analog voltage
	*eAR=((*adcDVal) * (3.3/1023));

}
