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

volatile freq_op_t freq_op;
volatile uint8_t traffic_light_state;

void HS_timer_callback() {
    EVENT_set(EVENT_HS_TIMER_TICK);
}

void NS_timer_callback() {
    EVENT_set(EVENT_NS_TIMER_TICK);
}

void high_freq_op() {
    switch (traffic_light_state) {
        case STATE_HS_GRUEN:
            if (EVENT_is_set(EVENT_HS_TIMER_TICK) && (EVENT_is_set(EVENT_FG_ARRIVED) || EVENT_is_set(EVENT_NS_ARRIVED))) {  // switch to NS traffic now
                USART_Transmit_s("Switching from HS to NS.\n");
                traffic_light_state = STATE_NS_GRUEN;
                TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_HFOP_NS_GREEN_PHASE * 1000, NS_timer_callback);
                TIMER_Start(TIMER_TRAFFIC_LIGHT);
                LIGHT_HFOP_set_NS();
            }
            break;
        case STATE_NS_GRUEN:
            if (EVENT_is_set(EVENT_NS_TIMER_TICK)) {  // switch to HS traffic now
                USART_Transmit_s("Switching from NS to HS.\n");
                traffic_light_state = STATE_HS_GRUEN;
                TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_HFOP_HS_GREEN_PHASE * 1000, HS_timer_callback);
                TIMER_Start(TIMER_TRAFFIC_LIGHT);
                EVENT_clear(EVENT_FG_ARRIVED);
                EVENT_clear(EVENT_NS_ARRIVED);
                LIGHT_HFOP_set_HS();
            }
        default:
            break;
    }
}

//// void switch_freq_op(freq_op_t new_freq_op) {
////     //todo only if Hauptstraße frei ansonsten event setzten und behandeln
////     //todo only if not degraded op
////     freq_op = new_freq_op;
//// }

//todo ISR for communication with leitsystem

void setup() {
    LIGHT_Init();
    TIMER_Init();
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\n Starting...\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit('\n');
    freq_op = STATE_HIGH_FREQ_OP;
    traffic_light_state = STATE_NS_GRUEN;
    EVENT_set(EVENT_NS_TIMER_TICK);
}

int main() {
    setup();

    while (1) {
        switch (freq_op) {
            case STATE_HIGH_FREQ_OP:
                high_freq_op();
                break;
            case STATE_LOW_FREQ_OP:
                //todo
                break;
            case STATE_REMOTE_FREQ_OP:
                //todo
                break;
            case STATE_DEGRADED_OP:
                //todo
                break;

            default:
                break;
        }
    }
}
