/*
===============================================================================
File Name   : edit_mode.c
Description :
This file contains functions for user configuration
through keypad and LCD interface.

It provides:
- Edit mode menu display
- RTC parameter editing access
- Temperature setpoint editing access
- Numeric value entry through keypad

The user can navigate menus using the keypad
and update RTC settings or temperature setpoint.
===============================================================================
*/

#include<LPC21XX.H>
#include"types.h"
#include"uart.h"
#include"lcd.h"
#include"keypad.h"
//#include"keypad_defines.h"
#include"delay.h"


/*
===============================================================================
Function Declarations
===============================================================================
*/
s32 Get_KeyVal(void);

void Edit_RTC_Menu(s32 *hour,s32 *min,s32 *sec,s32 *date,s32 *month,s32 *year,s32 *day);

void Edit_setpoint(u32* setpoint);


/*
===============================================================================
Function Name : Edit_mode
Description   :
Displays the main edit menu and allows the user
to select RTC editing or setpoint editing.

Menu Options :
1. Edit RTC
2. Edit Setpoint
3. Exit

Parameters     :
hour     -> Pointer to hour value
min      -> Pointer to minute value
sec      -> Pointer to second value
date     -> Pointer to date value
month    -> Pointer to month value
year     -> Pointer to year value
day      -> Pointer to day value
setpoint -> Pointer to temperature setpoint

Return Value   :
None
===============================================================================
*/
void Edit_mode(s32 *hour,s32 *min,s32 *sec,s32 *date,s32 *month,s32 *year,s32 *day,u32* setpoint)

{
	u8 key;   // Stores menu selection key

	// Notify user through UART
	uart_tx_str("\r\n *** Time Ediiting mode is activated *******\r\n");

	while(1)
	{
		// Clear LCD screen
		CmdLCD(0x01);

		// Display menu on first line
		CmdLCD(0x80);

		CharLCD('1');

		CharLCD('.');

		StrLCD("EDIT RTC");

		// Display menu on second line
		CmdLCD (0xC0);

		CharLCD('2');

		CharLCD('.');

		StrLCD("E.SETPOINT");

		CharLCD('3');

		CharLCD('.');

		StrLCD("Ex");

		// Wait for key press
		while(ColStat());

		delay_ms(10);

		key=KeyVal();

		// Wait for key release
		while(!ColStat());

		switch(key)
		{
			case '1':

				// Open RTC editing menu
				Edit_RTC_Menu(hour,min,sec,date,month,year,day);

				break;

			case '2':

				// Open setpoint editing menu
				Edit_setpoint(setpoint);

				break;

			case '3':

				// Exit edit mode
				CmdLCD(0X01);

				return;
		}
	}
}


/*
===============================================================================
Function Name : Get_KeyVal
Description   :
Reads a multi-digit numeric value from the keypad.

Operations :
- Accepts numeric keys (0-9)
- Displays entered digits on LCD
- '=' key confirms entry
- '*' key deletes last digit

Parameters     :
None

Return Value   :
Entered numeric value
===============================================================================
*/
s32 Get_KeyVal(void)
{
    u8 key;          // Stores keypad input

    u32 num = 0;     // Stores entered number

    while(1)
    {
        // Wait for key press
        while(ColStat());

		delay_ms(10);

		key=KeyVal();

		// Wait for key release
		while(!ColStat());

		// Numeric key pressed
        if(key >= '0' && key <= '9')
        {
            // Append digit to existing number
            num = num*10 + (key-'0');

            // Display digit on LCD
            CharLCD(key);
        }

        // '=' key pressed, return entered value
        else if(key == '=')
        {
            return num;
        }

        // '*' key pressed, delete last digit
        else if(key == '*')
        {
            if(num > 0)
            {
                // Remove last digit
                num /= 10;

                // Move cursor left
                CmdLCD(0x10);

                // Erase displayed digit
                CharLCD(' ');

                // Move cursor left again
                CmdLCD(0x10);
            }
        }
    }
}
