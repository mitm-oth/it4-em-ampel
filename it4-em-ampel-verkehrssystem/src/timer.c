#include "timer.h"

// #define tcnt1_start 65534
#define tcnt1_start 65000

void (*volatile timer_func[8])() = {0};
volatile uint32_t timer_max[8] = {0};
volatile uint32_t timer[8] = {0};
volatile uint8_t Tenable = 0;

ISR(TIMER1_OVF_vect) {
    TCNT1 = tcnt1_start;  // Start value of timer

    for (uint8_t t = 0; t < 8; t++) {          // go through all timers
        if (Tenable & (1 << t)) {              // if enabled
            if (timer[t]++ >= timer_max[t]) {  // add one and check tick
                timer[t] -= timer_max[t];      // if limit reached reset timer
                timer_func[t]();               // and execute callback
            }
        }
    }
}

void setupTimers() {
    TCNT1 = tcnt1_start;                                   // Start value of timer
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));  // Timer/Counter Clock Sources clear
    TCCR1B |= (1 << CS10);                                 // => Prescaler to 1
    TIMSK1 |= (1 << TOIE1);                                // Timer/Counter Interrupt Mask Register

    sei();
}

void declareTimer(uint8_t t, uint32_t delay_us, void (*func)()) {
    timer_max[t] = delay_us;
    timer_func[t] = func;
};

void startTimer(uint8_t t) {
    cli();
    timer[t] = 0;
    Tenable |= 1 << t;
    sei();
};

void cancelTimer(uint8_t t) {
    cli();
    Tenable &= ~(1 << t);
    sei();
};
