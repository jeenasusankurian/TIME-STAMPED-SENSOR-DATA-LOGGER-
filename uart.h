#include"types.h"

void uart_init(void);

void uart_tx_char(unsigned char);

void uart_tx_str(unsigned char*);

					  
void uart_tx_int(unsigned int);

unsigned char uart_rx_char(void);

void UartTx_RTC_Time(u32,u32,u32);
void UartTx_RTC_date(u32,u32,u32);

