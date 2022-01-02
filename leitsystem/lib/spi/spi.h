#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5
#define DD_SS DDB2
#define DDR_SPI DDRB

void SPI_MasterInit(void);
char SPI_MasterTransmit(char data);

void SPI_select_SS();
void SPI_deselect_SS();
