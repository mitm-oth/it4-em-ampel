#ifndef __TIMER_H_
#define __TIMER_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

typedef uint8_t timer_t;

void setupTimers();

/**
 * @brief 
 * 
 * @param t Timer number: 0 - 7 
 * @param delay_us Timer delay in 10^-6 s
 * @param func     Timer callback on Tick
 */
void declareTimer(timer_t t, uint32_t delay_us, void (*func)());

void startTimer(timer_t t);

void cancelTimer(timer_t t);

#endif  // __TIMER_H_