#pragma once

#include "../../global_config.h"

#define SYSTEM_OK 0x00
#define SYSTEM_NOT_AVAILABLE 0x01
#define SYSTEM_NOT_OK 0x02

//* days of the week
typedef uint8_t day_t;
#define DAY_UNKNOWN ((day_t)0x00)
#define DAY_MONDAY ((day_t)0x01)
#define DAY_TUESDAY ((day_t)0x02)
#define DAY_WEDNESDAY ((day_t)0x03)
#define DAY_THURSDAY ((day_t)0x04)
#define DAY_FRIDAY ((day_t)0x05)
#define DAY_SATURDAY ((day_t)0x06)
#define DAY_SUNDAY ((day_t)0x07)
