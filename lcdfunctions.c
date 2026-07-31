/*
===============================================================================
File Name   : lcd.c
Description :
This file contains all functions required to interface a 16x2 LCD 
with the LPC21xx microcontroller.

It provides:
- LCD initialization in 8-bit mode
- Sending commands to LCD
- Displaying characters and strings
- Displaying integers and floating point numbers
- Creating and storing custom characters in CGRAM

The LCD is connected to Port 0 (P0.0 – P0.10).
===============================================================================
*/

#include<LPC21xx.h>
#include"delay.h"
#include"Lcd.h"
#include"types.h"
#include"define.h"

// LCD pin connections
#define LCD_DAT 8   // LCD data lines connected to P0.0 – P0.7
#define RS 16       // Register Select pin connected to P0.8
#define RW 18       // Read/Write pin connected to P0.9
#define EN 17       // Enable pin connected to P0.10


/*
Initialize the LCD in 8-bit mode.
Configures data and control pins as output
and sends required initialization commands.
*/
void InitLCD(void)
{
	// Set P0.0 – P0.10 as output pins
	IODIR0|=((255<<LCD_DAT)|(1<<RS)|(1<<RW)|(1<<EN));

	delay_ms(20);        // Wait for LCD power stabilization

	CmdLCD(0x30);        // 8-bit mode enable
	delay_ms(10);

	CmdLCD(0x30);        // Repeat for proper initialization
	delay_ms(1);

	CmdLCD(0x30);
	delay_ms(1);

	CmdLCD(0x38);        // 8-bit, 5x7 font, 1-line display
	CmdLCD(0x10);        // Display OFF
	CmdLCD(0x01);        // Clear display
	CmdLCD(0x06);        // Cursor auto increment
	CmdLCD(0x0F);        // Display ON, Cursor ON, Blinking ON
}


/*
Send a command to LCD.
RS = 0 for command mode.
*/
void CmdLCD(u8 cmd)
{
	IOCLR0=1<<RS;        // Clear RS ? Command mode
	DispLCD(cmd);
}


/*
Send a single character (data) to LCD.
RS = 1 for data mode.
*/
void CharLCD(u8 dat)
{
	IOSET0=1<<RS;        // Set RS ? Data mode
	DispLCD(dat);
}


/*
Common function to send command or data to LCD.
Controls RW and EN signals.
*/
void DispLCD(u8 val)
{
	IOCLR0=1<<RW;                    // RW = 0 ? Write operation
	WRITEBYTE(IOPIN0,LCD_DAT,val);   // Write byte to data pins

	IOSET0=1<<EN;        // Enable high
	delay_us(2);         // Small delay (minimum 450 ns)
	IOCLR0=1<<EN;        // Enable low

	delay_ms(2);         // Wait for LCD execution
}


/*
Display a string on LCD.
Displays characters until null character is found.
*/
void StrLCD(char *ptr)
{
	while(*ptr!='\0')
	{
		CharLCD(*ptr);
		ptr++;
	}
}


/*
Display an integer number on LCD.
Handles positive and negative numbers.
*/
void IntLCD(s32 num)
{
	u8 a[10];
	s8 i=0;

	if(num==0)
		CharLCD('0');
	else
	{
		if(num<0)
		{
			num=-num;
			CharLCD('-');
		}

		// Convert integer to ASCII (reverse order)
		while(num>0)
		{
			a[i++]=num%10+48;
			num=num/10;
		}

		// Display digits in correct order
		for(--i;i>=0;i--)
			CharLCD(a[i]);
	}
}


/*
Display a floating point number on LCD.
Displays 6 digits after decimal point.
*/
void FltLCD(f32 fnum)
{
	u32 num,i;

	if(fnum<0)
	{
		CharLCD('-');
		fnum=-fnum;
	}

	num=fnum;           // Extract integer part
	IntLCD(num);        // Display integer part
	CharLCD('.');       // Display decimal point

	// Display fractional part (6 digits)
	for(i=0;i<6;i++)
	{
		fnum=(fnum-num)*10;
		num=fnum;
		CharLCD(num+48);
	}
}


/*
Store a custom character pattern in LCD CGRAM.
This allows creation of user-defined characters.
*/
void StoreCustCharFont(void)
{
	u8 i,LUT[]={0x0E,0x11,0x11,0x0E,0x00,0x00,0x00,0x00};

	CmdLCD(0x40);    // Set CGRAM address

	for(i=0;i<8;i++)
	{
		CharLCD(LUT[i]);   // Load custom character pattern
	}
}
