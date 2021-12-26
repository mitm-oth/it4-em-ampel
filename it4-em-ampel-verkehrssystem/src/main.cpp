#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "../../global_config.h"
#include "lights.h"
#include "timer.h"
#include "uart.h"
#include "verkehrssystem_config.h"

volatile freq_op_t freq_op = STATE_HIGH_FREQ_OP;
volatile uint8_t traffic_light_state = EVENT_HS_GRUEN;

void HS_timer_callback() {
    EVENT_set(EVENT_HS_GRUEN);
}

void NS_timer_callback() {
    EVENT_set(EVENT_NS_GRUEN);
}

void high_freq_op() {
    switch (traffic_light_state) {
        case EVENT_HS_GRUEN:
            if (EVENT_is_set(EVENT_HS_TIMER_TICK) && (EVENT_is_set(EVENT_FG_EVENT) || EVENT_is_set(EVENT_NS_EVENT))) {  // switch to NS traffic now
                traffic_light_state = EVENT_NS_GRUEN;
                declareTimer(TIMER_TRAFFIC_LIGHT, TIME_HFOP_NS_GREEN_PHASE, NS_timer_callback);  //todo convert HIGH_FREQ_OP_NS_TIME to 10^-6 s
                startTimer(TIMER_TRAFFIC_LIGHT);
                LIGHT_HFOP_set_NS();
            }
            break;
        case EVENT_NS_GRUEN:
            if (EVENT_is_set(EVENT_NS_TIMER_TICK)) {  // switch to HS traffic now
                traffic_light_state = EVENT_HS_GRUEN;
                declareTimer(TIMER_TRAFFIC_LIGHT, TIME_HFOP_HS_GREEN_PHASE, HS_timer_callback);
                startTimer(TIMER_TRAFFIC_LIGHT);
                EVENT_clear(EVENT_FG_EVENT);
                EVENT_clear(EVENT_NS_EVENT);
                LIGHT_HFOP_set_HS();
            }
        default:
            break;
    }
}

void switch_freq_op(freq_op_t new_freq_op) {
    //todo only if Hauptstraße frei ansonsten event setzten und behandeln
    //todo only if not degraded op
    freq_op = new_freq_op;
}

//todo implement events
//todo ISR for FG event / NS event
//todo ISR for communication with leitsystem (set ns_time / hs_time)
//todo timer for gelb (FG hat kein gelb)

void setup() {
    //todo set ns_time, hs_time
    //todo init
    setupTimers();
    USART_Init(BAUDRATE);
}

void loop() {
    // switch (freq_op) {
    //     case HIGH_FREQ_OP:
    //         high_freq_op();
    //         break;
    //     case LOW_FREQ_OP:
    //         break;
    //     case REMOTE_FREQ_OP:
    //         break;
    //     case DEGRADED_OP:
    //         break;

    //     default:
    //         break;
    // }
}