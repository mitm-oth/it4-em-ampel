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
    LIGHT_LFOP();
    while (freq_op == STATE_LOW_FREQ_OP)
        _delay_ms(100);
}

void remote_freq_op() {
}

//todo spi interface
//todo lfop testen
//todo timer stop bevore declare?

void handle_communication() {
    //todo
    // char str_buf[BUFFER_SIZE * 3];
    // USART_getline(str_buf, sizeof(str_buf));
    // if (strcmp(str_buf, SW_STATE_HFOP)) {
    // } else if (strcmp(str_buf, SW_STATE_LFOP)) {
    // }
}

void MAIN_Init() {
    LIGHT_Init();
    TIMER_Init();
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\n Starting...\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit('\n');
    freq_op = STATE_LOW_FREQ_OP;  //STATE_HIGH_FREQ_OP;
    traffic_light_state = STATE_NS_GRUEN;
    EVENT_set(EVENT_NS_TIMER_TICK);

    // //setup SPI
    // pinMode(MISO, OUTPUT);
    // SPCR |= _BV(SPE);
    // SPCR |= _BV(SPIE);
    // SPI.attachInterrupt();
    // SPDR = 0x00;
}

int main() {
    MAIN_Init();

    while (1) {
        handle_communication();
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

// byte msgCommand = 0;
// byte msgLength = 0;
// byte msgIndex = 0;

// ISR(SPI_STC_vect) {
//     if (msgLength == 0)  //new Message
//         msgCommand = SPDR;

//     SPDR = 0;
//     switch (msgCommand + (msgIndex << 8)) {
//         // ---------------------------------------- REQ module type
//         case 1:
//             msgLength = 1;
//             SPDR = 'W';
//             break;

//         // ---------------------------------------- MSG module LED
//         case (2 + (0 << 8)):
//             msgLength = 2;
//             break;
//         case (2 + (1 << 8)):
//             statLED_state = SPDR;
//             statLED_update = true;
//             break;

//         // ---------------------------------------- REQ wire connections
//         case 3:
//             msgLength = 1;
//             SPDR = wirestates;
//             break;
//     }

//     SPIcounter++;
//     msgIndex++;
//     if (msgIndex >= msgLength) {  //end of message
//         msgCommand = 0;
//         msgLength = 0;
//         msgIndex = 0;
//     }
// }
