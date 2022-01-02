#include "spi.h"

void SPI_MasterInit(void) {
    // Set MOSI and SCK output, all others input
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
    // Set MISO as input
    DDR_SPI &= ~(1 << DD_MISO);
    // Enable SPI, Master, set clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    // Set SPI Data Modes
    SPCR |= (1 << CPOL) | (1 << CPHA);
}

char SPI_MasterTransmit(char cData) {
    // Start transmission
    SPDR = cData;
    // Wait for transmission complete
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

void SPI_select_SS() {
    PORTB &= ~(1 << PORTB2);  // PIN 10
}

void SPI_deselect_SS() {
    PORTB |= (1 << PORTB2);  // PIN 10
}
