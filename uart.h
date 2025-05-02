#include "Common.h"
#ifndef _UART_HEADER_FILE_
#define _UART_HEADER_FILE_

/* Function prototypes */
void uart0_init(void);
BYTE uart0_getchar(void);
void uart0_putchar(char ch);
void uart0_put(char *ptr_str);
BOOLEAN uart0_dataAvailable(void);

void uart2_init(void);
BYTE uart2_getchar(void);
void uart2_putchar(char ch);
void uart2_put(char *ptr_str);
BOOLEAN uart2_dataAvailable(void);

//int main(void);


#endif
