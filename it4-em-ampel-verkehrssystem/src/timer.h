#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

void setupTimers();

/**
 * @brief 
 * 
 * @param t Timer number: 0 - 7 
 * @param delay_us Timer delay in 10^-6 s
 * @param func     Timer callback on Tick
 */
void declareTimer(uint8_t t, uint32_t delay_us, void (*func)());

void startTimer(uint8_t t);

void cancelTimer(uint8_t t);
