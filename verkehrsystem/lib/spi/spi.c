#include "spi.h"

void SPI_Slave_Init() {
    // Set MISO output, all others input
    DDR_SPI |= (1 << DD_MISO);
    DDR_SPI &= ~((1 << DD_MISO) | (1 << DD_SCK) | (1 << DD_SS));
    // Enable SPI and SPI interrupts
    SPCR = (1 << SPE) | (1 << SPIE);
    sei();
    // Set SPI Data Modes
    SPCR |= (1 << CPOL) | (1 << CPHA);  //todo mit johannes absprechen
    SPDR = 0x00;
}

////* handled by interrupts
//// char SPI_Slave_Receive() {
////     // Wait for reception complete
////     while (!(SPSR & (1 << SPIF)))
////         ;
////     // Return Data Register
////     return SPDR;
//// }

ISR(SPI_STC_vect) {
    uint8_t data = SPDR;
    if (data == Q_ERROR_CODE) {
        SPDR = error_code;
    } else
        spi_command_to_freq_op(SPDR);
}
