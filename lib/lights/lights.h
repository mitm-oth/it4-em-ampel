#pragma once

#include <avr/interrupt.h>
#include <events.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>   // Only for debug()
#include <stdlib.h>  // Only for debug()
#include <uart.h>    // Only for debug()
#ifdef VERKEHRSSYSTEM
#include <../../include/verkehrssystem_config.h>  //todo find a better way to include this
#elif defined LEITSYSTEM
#include <../../include/leitsystem_config.h>  //todo find a better way to include this
#endif

void LIGHT_Init();

bool LIGHTS_FG_is_pressed();
bool LIGHTS_NS_is_pressed();

void LIGHT_HFOP_set_HS();
void LIGHT_HFOP_set_NS();

void LIGHT_LFOP();
void LIGHT_debug();
