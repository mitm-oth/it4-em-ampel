#ifdef LEITSYSTEM

#include <events.h>
#include <leitsystem/spi.h>
#include <leitsystem_config.h>
#include <uart.h>

void setup() {
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit_s("\nLEITSYSTEM v0.1\n\n");

    SPI_MasterInit();
}

void loop() {
    _delay_ms(5000);
    SPI_select_SS();
    SPI_MasterTransmit(0x01);
    USART_Transmit_s("0x01\n");
    SPI_deselect_SS();
    _delay_ms(5000);
    SPI_select_SS();
    SPI_MasterTransmit(0x02);
    USART_Transmit_s("0x02\n");
    SPI_deselect_SS();
}

int main() {
    setup();
    while (1)
        loop();
    return 0;
}

#endif
