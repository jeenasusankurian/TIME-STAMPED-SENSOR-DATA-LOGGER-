/*
===============================================================================
File Name   : edit_rtc.c
Description :
This file contains functions for editing RTC
parameters and temperature setpoint values.

It provides:
- RTC time and date editing through keypad
- LCD based user interface
- UART notification for edit mode
- Temperature setpoint configuration

The user can modify RTC parameters such as
hour, minute, second, date, month, year and day.
===============================================================================
*/

#include<LPC21XX.H>
#include"types.h"
#include"uart.h"
#include"lcd.h"
#include"keypad.h"
//"keypad_defines.h"
#include"delay.h"


/*
===============================================================================
Function Declaration
===============================================================================
*/
u32 Get_KeyVal(void);


/*
===============================================================================
Global Variables
===============================================================================
*/
s8 option;      // Stores menu selection

s32 value;      // Stores entered value


/*
===============================================================================
Function Name : Edit_RTC_Menu
Description   :
Displays RTC edit menu on LCD and allows user
to modify RTC parameters using keypad input.

Editable Parameters :
- Hour
- Minute
- Second
- Date
- Month
- Year
- Day

Parameter     :
hour  -> Pointer to hour value
min   -> Pointer to minute value
sec   -> Pointer to second value
date  -> Pointer to date value
month -> Pointer to month value
year  -> Pointer to year value
day   -> Pointer to day value

Return Value  :
None
===============================================================================
*/
void Edit_RTC_Menu(s32 *hour,s32 *min,s32 *sec,s32 *date,s32 *month,s32 *year,s32 *day)
{
	// Notify user through UART
	uart_tx_str("\r\n *** Time Ediiting mode is activated *******\r\n");

	while(1)
	{
		// Display RTC edit menu
		CmdLCD(0x10);

		CmdLCD(0x80);

		StrLCD("1.H 2.m 3.S 4.D");

		CmdLCD(0Xc0);

		StrLCD("5.M 6.y 7.d 8.E");

		// Wait for key press
		while(ColStat());

		delay_ms(10);

		option=KeyVal();

		// Wait for key release
		while(!ColStat());

		switch(option)
		{
			case '1':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set hour");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>0&&value<=23)

				HOUR=value;

				break;

			case '2':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set min");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>0&&value<=59)

				MIN=value;

				break;

			case '3':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set sec");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>0&&value<=59)

				SEC=value;

				break;

			case '4':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set date");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>0&&value<=31)

				DOM=value;

				break;

			case '5':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set month");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>=1&&value<=12)

				MONTH=value;

				break;

			case '6':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set year");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>0&&value<=26)

				YEAR=value;

				break;

			case '7':
				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("set day");

				CharLCD(':');

				value=Get_KeyVal();

				if(value>=0&&value<=6)

				DOW=value;

				break;

			case '8':

				// Exit edit menu
				return;
		}
	}
}


/*
===============================================================================
Function Name : Edit_setpoint
Description   :
Allows the user to modify the temperature
setpoint value using keypad input.

Valid Range :
1 to 99

Parameter     :
setpoint -> Pointer to temperature setpoint

Return Value  :
None
===============================================================================
*/
void Edit_setpoint(u32 *setpoint)
{
	// Display setpoint entry screen
	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("SET POINT:");

	// Read setpoint from keypad
	value=Get_KeyVal();

	// Validate entered value
	if(value>0&&value<100)
	{
		*setpoint=value;

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Set point updated");
	}
	else
	{
		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid set point");
	}
}
