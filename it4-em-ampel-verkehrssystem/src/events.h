#ifndef __EVENTS_H_
#define __EVENTS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>   // Only for debug()
#include <stdlib.h>  // Only for debug()

#include "uart.h"  // Only for debug()

typedef uint16_t event_t;  //todo change to 8 Bit if possible

void EVENT_set(event_t event);
void EVENT_clear(event_t event);

bool EVENT_is_set(event_t event);

void EVENT_debug();

#endif  // __EVENTS_H_