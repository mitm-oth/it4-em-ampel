//* Betriebszustände des Ampelsystems
#define HIGH_FREQ_OP 0x00
#define LOW_FREQ_OP 0x01
#define REMOTE_FREQ_OP 0x02
#define DEGRADED_OP 0x03

//* Error codes
#define NO_ERROR 0x00
#define RED_LIGHT_MR 0x10
#define RED_LIGHT_SR 0x11
#define RED_LIGHT_P 0x12
#define YELLOW_LIGHT_SR 0x13
#define FLASH_ERROR 0x20
#define SRAM_ERROR 0x21
#define STACK_ERROR 0x22
#define SW_ERROR 0x80
#define TIME_ERROR 0x81

//* SPI Stuff
