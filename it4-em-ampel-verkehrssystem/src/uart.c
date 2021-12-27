#include "uart.h"

#define XOFF 0x13
#define XON 0x11

uint8_t buffer[BUFFER_SIZE] = {0};
uint8_t head = 0;
uint8_t tail = 0;
bool me_xoff_flag = false;
bool you_xoff_flag = false;

void push(uint8_t data) {
    cli();
    buffer[head] = data;
    head = (head + 1) % BUFFER_SIZE;
    sei();
}

uint8_t USART_pop() {
    cli();
    uint8_t last = buffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    sei();
    return last;
}

bool USART_buffer_empty() {
    cli();
    bool empty = (head == tail);
    sei();
    return empty;
}

void USART_getline(char buffer[], size_t size) {
    int i = 0;
    while (i < size && !USART_buffer_empty()) {
        buffer[i] = USART_pop();
        if (buffer[i] == '\0' || buffer[i] == '\n' || buffer[i] == XON || buffer[i] == XOFF)
            break;
        i++;
    }
    buffer[i] = '\0';
}

bool USART_buffer_full() {
    bool full = (((head + 1) % BUFFER_SIZE) == tail);
    return full;
}

uint8_t USART_buffer_fill_state() {
    return (head - tail) % BUFFER_SIZE;
}

// USART RX Interrupt
ISR(USART_RX_vect) {
    uint8_t data = UDR0;
    if (data == XON) {
        me_xoff_flag = false;
    } else if (data == XOFF) {
        me_xoff_flag = true;
    } else if (!USART_buffer_full()) {
        push(data);
    }
}

// char USART_Receive() {
//     while (!(UCSR0A & (1 << RXC0))) {
//     }
//     return UDR0;
// }

void USART_Init(uint32_t baud_rate) {
    //* Set baud rate
    uint32_t baud_const = (((F_CPU / (baud_rate * 16UL))) - 1);
    UBRR0H = (baud_const >> 8);
    UBRR0L = baud_const;
    //* Enable Recieve and Transmit
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    //* Set USART interrupt enable
    UCSR0B |= (1 << RXCIE0);
}

void USART_Transmit(char data) {
    while (me_xoff_flag || !(UCSR0A & (1 << UDRE0))) {
        _delay_ms(1);
    }
    UDR0 = data;
}

void USART_Transmit_s(const char *data) {
    for (int f = 0; data[f] != '\0'; f++)
        USART_Transmit(data[f]);
}

void USART_Transmit_s_f(const char *data_in_flash) {
    int f = 0;
    char data;
    while (true) {
        data = pgm_read_byte(data_in_flash + f++);
        if (data == '\0')
            break;
        USART_Transmit(data);
    }
}

void USART_mainloop() {
    if (you_xoff_flag && USART_buffer_fill_state() <= HYSTERESE_BUFFER_LOW) {
        USART_Transmit(XON);
        you_xoff_flag = false;
    } else if (!you_xoff_flag && USART_buffer_fill_state() > HYSTERESE_BUFFER_HIGH) {
        USART_Transmit(XOFF);
        you_xoff_flag = true;
    }
}