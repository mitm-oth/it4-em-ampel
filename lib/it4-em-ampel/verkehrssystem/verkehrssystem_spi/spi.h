#include <../../include/verkehrssystem_config.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5
#define DD_SS DDB2
#define DDR_SPI DDRB

void SPI_Slave_Init();
//// char SPI_Slave_Receive();
