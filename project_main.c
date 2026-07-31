/*
===============================================================================
File Name   : main.c
Description :
This file contains the main application for a
Temperature Monitoring and RTC Display System
using LPC21xx microcontroller.

It provides:
- Real Time Clock (RTC) display
- Temperature monitoring using LM35 sensor
- LCD display of date, time and temperature
- UART status and alert messages
- Setpoint based LED indication
- Edit mode using switch and keypad

The system continuously monitors temperature
and compares it with a user-defined setpoint.
===============================================================================
*/

#include <lpc21xx.h>
#include "RTC.h"
#include "lcd.h"
#include "uart.h"
#include "adc.h"
#include "adc_defines.h"
#include "types.h"
#include "delay.h"
#include "keypad.h"
#include "lm35.h"

/* Switch and LED pin definitions */
#define SW 6      // Switch connected to P0.6
#define LED 5     // LED connected to P0.5


/*
===============================================================================
Function Declarations
===============================================================================
*/
void DisplayTemp(u32);
void Edit_mode(s32 *,s32 *,s32 *,s32*,s32*,s32*,s32*,u32*);
void UART_Info(u32 temp);
void UART_Alert(u32 temp);


/*
===============================================================================
Global Variables
===============================================================================
*/
s32 hour,min,sec,date,month,year,day;   // RTC parameters

u32 temp=0;                             // Temperature value

u32 setpoint=45;                        // Temperature threshold value


/*
===============================================================================
Function Name : main
Description   :
Main application function.

Operations :
- Initializes RTC, LCD, UART, ADC and Keypad
- Sets default time, date and day
- Continuously reads RTC and temperature data
- Displays information on LCD
- Sends UART alerts when temperature exceeds setpoint
- Sends periodic UART information messages
- Controls LED based on temperature condition
- Enters edit mode when switch is pressed

Parameters    :
None

Return Value  :
None
===============================================================================
*/
int main()
{
	static s32 last_alert_sec = -1;   // Stores last alert second

    static s32 last_info_min  = -1;   // Stores last info minute

	// Initialize RTC
	RTC_Init();

	// Initialize LCD
	InitLCD();

	// Initialize UART
	uart_init();

	// Initialize ADC channel 1
	Init_ADC(CH1);

	// Initialize keypad
	KeypadInit();

	// Configure LED pin as output
	IODIR0|=(1<<LED);

	// Set initial RTC time (HH:MM:SS)
	SetRTCTimeInfo(18,9,0);

	// Set initial RTC date (DD:MM:YY)
	SetRTCDateInfo(8,1,26);

	// Set initial day value
	SetRTCDay(4);

	while(1)
	{
		// Read current RTC time
		GetRTCTimeInfo(&hour,&min,&sec);

		// Read current day
		GetRTCDay(&day);

		// Read current date
		GetRTCDateInfo(&date,&month,&year);

		// Read temperature from LM35 sensor
		temp = Read_LM35('C');

		// Display current time on LCD
		DisplayRTCTime(hour,min,sec);

		// Display current day on LCD
		DisplayRTCDay(day);

		// Display current date on LCD
		DisplayRTCDate(date,month,year);

		// Display temperature on LCD
		DisplayTemp(temp);

		// Check if temperature exceeds setpoint
		if(Read_LM35('C') > setpoint)
		{
			// Turn ON LED
			IOSET0=1<<LED;

			// Send alert only once per second
			if(sec != last_alert_sec)
			{
				last_alert_sec = sec;

				UART_Alert(temp);
			}
		}
		else
		{
			// Turn OFF LED
			IOCLR0=1<<LED;

			// Send status information once per minute
			if(min != last_info_min)
			{
				last_info_min = min;

				UART_Info(temp);
			}
		}

		// Check if switch is pressed
		if(((IOPIN0>>SW)&1)==0)
		{
			// Wait until switch is released
			while(((IOPIN0>>SW)&1)==0);

			// Enter edit mode for RTC and setpoint configuration
			Edit_mode(&hour,&min,&sec,
			          &date,&month,&year,
			          &day,&setpoint);
		}

		// Optional delay
		// delay_ms(200);
	}
}