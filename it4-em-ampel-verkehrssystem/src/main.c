#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "../../global_config.h"
#include "lights.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "verkehrssystem_config.h"

volatile freq_op_t freq_op;
volatile uint8_t traffic_light_state;
volatile error_t error_code = ERROR_NO_ERROR;

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
                EVENT_clear(EVENT_HS_TIMER_TICK);
                EVENT_clear(EVENT_NS_TIMER_TICK);
                EVENT_clear(EVENT_FG_ARRIVED);
                EVENT_clear(EVENT_NS_ARRIVED);
                TIMER_Cancel(TIMER_TRAFFIC_LIGHT);
                USART_Transmit_s("Switching from HS to NS.\n");
                traffic_light_state = STATE_NS_GRUEN;
                LIGHT_HFOP_set_NS();
                TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_HFOP_NS_GREEN_PHASE, NS_timer_callback);
                TIMER_Start(TIMER_TRAFFIC_LIGHT);
            }
            break;
        case STATE_NS_GRUEN:
            if (EVENT_is_set(EVENT_NS_TIMER_TICK)) {  // switch to HS traffic now
                EVENT_clear(EVENT_HS_TIMER_TICK);
                EVENT_clear(EVENT_NS_TIMER_TICK);
                TIMER_Cancel(TIMER_TRAFFIC_LIGHT);
                USART_Transmit_s("Switching from NS to HS.\n");
                traffic_light_state = STATE_HS_GRUEN;
                LIGHT_HFOP_set_HS();
                TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_HFOP_HS_GREEN_PHASE, HS_timer_callback);
                TIMER_Start(TIMER_TRAFFIC_LIGHT);
            }
        default:
            break;
    }
}

void low_freq_op() {
    LIGHT_LFOP();  // Blink is Handled by interrupts
    while (freq_op == STATE_LOW_FREQ_OP)
        _delay_ms(100);
}

void remote_freq_op() {
    while (freq_op == STATE_REMOTE_FREQ_OP)
        _delay_ms(100);
}

void MAIN_Init() {
    LIGHT_Init();
    TIMER_Init();
    SPI_Slave_Init();
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\n Starting...\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit('\n');
    freq_op = STATE_HIGH_FREQ_OP;  //STATE_HIGH_FREQ_OP;
    traffic_light_state = STATE_NS_GRUEN;
    EVENT_set(EVENT_NS_TIMER_TICK);
}

int main() {
    MAIN_Init();

    while (1) {
        switch (freq_op) {
            case STATE_HIGH_FREQ_OP:
                high_freq_op();
                break;
            case STATE_LOW_FREQ_OP:
                low_freq_op();
                break;
            case STATE_REMOTE_FREQ_OP:
                remote_freq_op();
                break;
            case STATE_DEGRADED_OP:
                USART_Transmit_s("ERROR ");
                USART_Transmit(error_code);
                exit(EXIT_FAILURE);  //wait till hard reset

            default:
                break;
        }
    }

    return 0;
}
