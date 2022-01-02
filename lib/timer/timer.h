#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

typedef uint8_t timer_t;

void TIMER_Init();

/**
 * @brief 
 * 
 * @param t Timer number: 0 - 7 
 * @param delay_us Timer delay in 10^-6 s //todo ms
 * @param func     Timer callback on Tick
 */
void TIMER_Declare(timer_t t, uint32_t delay_us, void (*func)());

void TIMER_Start(timer_t t);

void TIMER_Cancel(timer_t t);
