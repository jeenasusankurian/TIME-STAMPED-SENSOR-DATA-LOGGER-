#include <LPC21xx.H>
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart.h"
#include "lm35.h"



// Array to hold names of days of the week
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};


/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
	
	PCONP |= (1 << 9);  
  // Disable and reset the RTC
	CCR = RTC_RESET;
  
#ifdef _LPC2148
  // Enable the RTC & select the clock source
	CCR = RTC_ENABLE | RTC_CLKSRC;  
#else
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC= PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE;  
	
#endif

}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

/*
This function will Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
		CmdLCD(0x80);
		CharLCD((hour/10)+48);
		CharLCD((hour%10)+48);
		CharLCD(':');
		CharLCD((minute/10)+48);
		CharLCD((minute%10)+48);
		CharLCD(':');
		CharLCD((second/10)+48);
		CharLCD((second%10)+48);

}

/*
This function will Display the RTC time on 
UART serial winodw/hyperterminal in the below form
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/

void DisplayRTCTime_uart(u32 Hour, u32 Minute, u32 Second)
{
	    uart_tx_char((Hour/10)+48);
		uart_tx_char((Hour%10)+48);
		uart_tx_char(':');
		uart_tx_char((Minute/10)+48);
		uart_tx_char((Minute%10)+48);
		uart_tx_char(':');
		uart_tx_char((Second/10)+48);
		uart_tx_char((Second%10)+48);
}

/*
This function will set the 
Set the RTC time
Hour to set (0 23)
Minute to set (0 59)
Second to set (0 59)
*/


void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}



/*
This function is used to 
Get the current RTC date
day Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*

This function will Display the RTC date on LCD
Day of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
		CmdLCD(0xC0);
		CharLCD((date/10)+48);
		CharLCD((date%10)+48);
		CharLCD('/');
		CharLCD((month/10)+48);
		CharLCD((month%10)+48);
		CharLCD('/');
	    CharLCD((year/10)+48);
		CharLCD((year%10)+48);
	
}

/*This function will dispaly the the RTC date on UART window/hyper terminal
Day of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'*/

void DisplayRTCDate_uart(u32 Date, u32 Month, u32 Year)
		{
        uart_tx_char((Date/10)+48);
		uart_tx_char((Date%10)+48);
		uart_tx_char('/');
		uart_tx_char((Month/10)+48);
		uart_tx_char((Month%10)+48);
		uart_tx_char('/');
		uart_tx_char((Year/10)+48);
		uart_tx_char((Year%10)+48);
		}


/*
This function will Set the RTC date
day of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;	
}



/*
This function will Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *day)
{
	*day = DOW; 
}

/*
This function will display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u32 dow)
{
	CmdLCD(0x8A);
	StrLCD(week[dow]);  
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 day)
{
	DOW = day;
}



