/*
===============================================================================
File Name   : uart.c
Description :
This file contains UART0 driver functions for LPC21xx
microcontrollers.

It provides:
- UART initialization
- Character transmission
- String transmission
- Character reception
- Integer transmission

UART0 is configured for serial communication using
the onboard UART peripheral.
===============================================================================
*/

#include<LPC21XX.H>

/* UART0 Line Status Register bit positions */
#define U0THRE 5   // Transmit Holding Register Empty bit
#define U0RDR  0   // Receiver Data Ready bit

/* UART0 pin and control bit definitions */
#define Txd0   0   // P0.0 configured as TXD0
#define DLAB   7   // Divisor Latch Access Bit


/*
===============================================================================
Function Name : uart_init
Description   :
Initializes UART0 for serial communication.

Operations :
- Enables TXD0 pin function
- Enables divisor latch access
- Configures baud rate
- Sets UART frame format
- Enables and resets FIFOs

Parameters    : None

Return Value  : None
===============================================================================
*/
void uart_init(void)
{
	PINSEL0|=(1<<Txd0);	// enabling the p0.0 for the uart transmission

	U0LSR=1<<DLAB;	// enabling the divisor latch bit for accessing the baudrate of 9600 and setting the DLL and DLM

	U0DLL=97;	// FOR THE 9600 BAUD RATE

	U0DLM=0;	// IF U0DLL=0-255 then, UODLM=0;

	U0LSR=0X03;	// uart frame format is enabling for the 8 bit transmission one stop bit ,no parity

	U0FCR=0x07;	// enabling the FIFO ,reset RXFIFO,reset TXFIFO
}


/*
===============================================================================
Function Name : uart_tx_char
Description   :
Transmits a single character through UART0.

Parameter     :
data -> Character to be transmitted

Return Value  :
None
===============================================================================
*/
void uart_tx_char(unsigned char data)
{
	while(((U0LSR>>U0THRE)&1)==0);	// wait until the U0THR(uart 0 transmitt holding register) become empty

	U0THR=data;	// load character into transmit register
}


/*
===============================================================================
Function Name : uart_tx_str
Description   :
Transmits a null terminated string through UART0.

Parameter     :
pchar -> Pointer to string

Return Value  :
None
===============================================================================
*/
void uart_tx_str(unsigned char *pchar)
{
	while(*pchar!='\0')	// continue until end of string

	uart_tx_char(*pchar);	// transmit current character

	pchar++;	// move pointer to next character
}


/*
===============================================================================
Function Name : uart_rx_char
Description   :
Receives a single character from UART0.

Parameter     :
None

Return Value  :
Received character
===============================================================================
*/
unsigned char uart_rx_char(void)
{
	char data;	// variable to store received data

	while(((U0LSR>>U0RBR)&1)==0);	// reading the receiver byte ready bit and wait until unread data is available

	data=U0RDR;	// read received data

	return data;	// return received character
}


/*
===============================================================================
Function Name : uart_tx_int
Description   :
Transmits an integer value through UART0.

Parameter     :
data -> Integer value to be transmitted

Return Value  :
None
===============================================================================
*/
void uart_tx_int(unsigned int data)
{
	unsigned char a[10];	// array to store digits

	char i=0;	// digit index

	if(data==0)
	{
		uart_tx_char('0');	// transmit zero
	}
	else
	{
		if(data<0)
		{
			data=-data;	// convert negative value to positive

			uart_tx_char('-');	// transmit negative sign
		}

		while(data>0)
		{
			a[i++]=(data%10)+48;	// extract digit and convert to ASCII

			data=data/10;	// remove last digit
		}

		for(i=i-1;i>=0;i--)
		{
			uart_tx_char(a[i]);	// transmit digits in correct order
		}
	}
}
