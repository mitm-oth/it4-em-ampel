#ifndef __LIGHTS_H_
#define __LIGHTS_H_

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>   // Only for debug()
#include <stdlib.h>  // Only for debug()

#include "../../global_config.h"
#include "events.h"
#include "uart.h"  // Only for debug()
#include "verkehrssystem_config.h"

void LIGHT_Init();

bool LIGHTS_FG_is_pressed();
bool LIGHTS_NS_is_pressed();

void LIGHT_HFOP_set_HS();
void LIGHT_HFOP_set_NS();

void LIGHT_LFOP();
void LIGHT_debug();

#endif  // __LIGHTS_H_