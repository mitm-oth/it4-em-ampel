#ifndef __UART_H__
#define __UART_H__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <util/delay.h>

#define BAUDRATE 9600

#define BUFFER_SIZE 64
#define HYSTERESE_BUFFER_HIGH 24
#define HYSTERESE_BUFFER_LOW 4

void USART_Init(uint32_t baud_rate);
void USART_Transmit(char data);
void USART_Transmit_s(const char *data);
void USART_Transmit_s_f(const char *data);
void USART_mainloop();

// Buffer operations
uint8_t pop();
bool buffer_full();
bool buffer_empty();
uint8_t buffer_fill_state();

#endif  // __UART_H__