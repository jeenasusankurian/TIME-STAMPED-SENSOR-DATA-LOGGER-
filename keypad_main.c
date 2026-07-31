/*
===============================================================================
File Name   : keypad.c
Description :
This file contains functions for interfacing a
4x4 Matrix Keypad with LPC21xx microcontroller.

It provides:
- Keypad initialization
- Column status detection
- Key value detection

The keypad is connected using 4 rows and 4 columns.
Rows are configured as outputs and columns as inputs.
===============================================================================
*/

#include<LPC21xx.h>
#include"KeyPad_defines.h"
#include"types.h"
#include"delay.h"


/*
===============================================================================
Function Name : KeypadInit
Description   :
Initializes the 4x4 keypad interface.

Operations :
- Configures keypad pins as GPIO
- Sets row pins as outputs
- Sets column pins as inputs
- Initializes all rows to logic low

Parameters    :
None

Return Value  :
None
===============================================================================
*/
void KeypadInit(void)
{
    PINSEL2 = 0x00000000;   // Configure keypad pins as GPIO

    IODIR1 |=  (1<<R0)|(1<<R1)|(1<<R2)|(1<<R3);   // Configure rows as output

    IODIR1 &= ~((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3)); // Configure columns as input

	IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));     // Initialize all rows to low

   // IOSET1 = (1<<R0)|(1<<R1)|(1<<R2)|(1<<R3);  // Alternative initialization with rows high
}


/*
===============================================================================
Old Keypad Initialization Method
===============================================================================
*/
/*
void KeyPdInit(void)

{

		IODIR1|=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

	    // P1.16-P1.19 are configured as outputs

		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

		// Initialize rows to logic low

}
*/


/*
===============================================================================
Function Name : ColStat
Description   :
Checks the status of keypad columns.

Operations :
- Reads all column inputs
- Detects if any key is pressed

Parameters    :
None

Return Value  :
1 -> No key pressed
0 -> Key pressed
===============================================================================
*/
u8 ColStat(void)
{
	if((((IOPIN1>>20)&0x0f)==0x0f))

		return 1;   // No key pressed

	else 

		return 0;   // Key press detected
}


/*
===============================================================================
Function Name : KeyVal
Description   :
Identifies the key pressed on the keypad.

Operations :
- Activates each row one by one
- Detects the corresponding column
- Determines row and column position
- Returns key value using lookup table

Parameters    :
None

Return Value  :
Pressed key value from LUT
===============================================================================
*/
u8 KeyVal(void)
{
		char row_val=0,col_val=0;   // Variables to store row and column number

		// Check Row 0
		IOCLR1=(1<<R0);

		IOSET1=((1<<R1)|(1<<R2)|(1<<R3));

		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=0;

			goto colcheck;
		}

		// Check Row 1
		IOCLR1=(1<<R1);

		IOSET1=((1<<R0)|(1<<R2)|(1<<R3));

		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=1;

			goto colcheck;
		}

		// Check Row 2
		IOCLR1=(1<<R2);

		IOSET1=((1<<R0)|(1<<R1)|(1<<R3));

		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=2;

			goto colcheck;
		}

		// Check Row 3
		IOCLR1=(1<<R3);

		IOSET1=((1<<R0)|(1<<R1)|(1<<R2));

		if((((IOPIN1>>20)&0x0f)!=0x0f))

			row_val=3;


		/*
		-----------------------------------------------------------------------
		Column Detection
		-----------------------------------------------------------------------
		*/
		colcheck:

		if(((IOPIN1>>C0)&1)==0)

			col_val=0;   // Column 0 active

		else if(((IOPIN1>>C1)&1)==0)

			col_val=1;   // Column 1 active

		else if(((IOPIN1>>C2)&1)==0)

			col_val=2;   // Column 2 active

		else

			col_val=3;   // Column 3 active


		// Reset all rows to low state
		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));

		// Return key value from lookup table
		return(LUT[row_val][col_val]);
}
