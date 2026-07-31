#ifndef RTC_H
#define RTC_H

#include "types.h"   // Include user-defined data types like s32, u32

// External global variables to store RTC values
extern s32 hour,min,sec,date,month,year,day;

/*
Initialize the Real Time Clock (RTC)
Configures and enables RTC module
*/
void RTC_Init(void);

/*
Get the current RTC time
Parameters:
Pointer to hour
Pointer to minute
Pointer to second
*/
void GetRTCTimeInfo(s32 *,s32 *,s32 *);

/*
Display the given time on LCD
Parameters:
Hour (0–23)
Minute (0–59)
Second (0–59)
*/
void DisplayRTCTime(u32,u32,u32);

/*
Get the current RTC date
Parameters:
Pointer to date (1–31)
Pointer to month (1–12)
Pointer to year (four digits)
*/
void GetRTCDateInfo(s32 *,s32 *,s32 *);

/*
Display the given time on LCD
Hour (0–23)
Minute (0–59)
Second (0–59)
(Note: Function declared again as in original code)
*/
void DisplayRTCTime(u32,u32,u32);

/*
Display the given date on LCD
Parameters:
Date (1–31)
Month (1–12)
Year (four digits)
*/
void DisplayRTCDate(u32,u32, u32);

/*
Set the RTC time
Parameters:
Hour (0–23)
Minute (0–59)
Second (0–59)
*/
void SetRTCTimeInfo(u32,u32,u32);

/*
Set the RTC date
Parameters:
Date (1–31)
Month (1–12)
Year (four digits)
*/
void SetRTCDateInfo(u32,u32,u32);

/*
Get the current day of week
Pointer to store day (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *);

/*
Display the current day of week on LCD
Parameter:
Day of week (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u32);

/*
Set the day of week in RTC
Parameter:
Day of week (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32);

/*
Display the current RTC time on UART
Format: HH:MM:SS
*/
void DisplayRTCTime_uart(u32,u32,u32);

/*
Display the current RTC date on UART
Format: DD/MM/YY
*/
void DisplayRTCDate_uart(u32,u32,u32);

#endif

