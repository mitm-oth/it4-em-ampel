//* Betriebszustände des Ampelsystems
#define High_freq_op 0x00
#define Low_freq_op 0x01
#define Remote_freq_op 0x02
#define Degraded_op 0x03

//* Error codes
#define No_error 0x00
#define Red_light_MR 0x10
#define Red_light_SR 0x11
#define Red_light_P 0x12
#define Yellow_light_SR 0x13
#define Flash_error 0x20
#define SRAM_error 0x21
#define Stack_error 0x22
#define SW_error 0x80
#define Time_error 0x81

//* SPI Stuff
