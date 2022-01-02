#ifdef LEITSYSTEM

#include <events.h>
#include <leitsystem_config.h>
#include <uart.h>

void setup() {
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit_s("\nLEITSYSTEM v0.1\n\n");
}

void loop() {
    _delay_ms(100);
}

int main() {
    setup();
    while (1)
        loop();
    return 0;
}

#endif
