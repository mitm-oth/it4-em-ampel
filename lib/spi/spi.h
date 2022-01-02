#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef VERKEHRSSYSTEM
#include <../../include/verkehrssystem_config.h>  //todo find a better way to include this
#elif defined LEITSYSTEM
#include <../../include/leitsystem_config.h>  //todo find a better way to include this
#endif

#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5
#define DD_SS DDB2
#define DDR_SPI DDRB

void SPI_Slave_Init();
//// char SPI_Slave_Receive();
