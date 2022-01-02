#include "lights.h"

#include <../../include/verkehrssystem_config.h>

#define ON true
#define OFF false

#define HS_G 0
#define HS_Y 1
#define HS_R 2
#define NS_G 3
#define NS_Y 4
#define NS_R 5
#define FG_G 6
#define FG_R 7

volatile bool lights[8] = {0};

// FG pressd button
ISR(INT0_vect) {
    EVENT_set(EVENT_FG_ARRIVED);
}
// Car is on induction plate
ISR(INT1_vect) {
    EVENT_set(EVENT_NS_ARRIVED);
}

void on(uint8_t light_pos) {
    lights[light_pos] = ON;
    switch (light_pos) {
        case HS_G:
            PORTB |= (1 << PORTB0);
            break;
        case HS_Y:
            PORTB |= (1 << PORTB1);
            break;
        case HS_R:
            PORTD |= (1 << PORTD4);
            break;
        case NS_G:
            PORTD |= (1 << PORTD5);
            break;
        case NS_Y:
            PORTD |= (1 << PORTD6);
            break;
        case NS_R:
            PORTD |= (1 << PORTD7);
            break;
        case FG_G:
            // No pin connected here
            break;
        case FG_R:
            // No pin connected here
            break;

        default:
            break;
    }
}

void off(uint8_t light_pos) {
    lights[light_pos] = OFF;
    switch (light_pos) {
        case HS_G:
            PORTB &= ~(1 << PORTB0);
            break;
        case HS_Y:
            PORTB &= ~(1 << PORTB1);
            break;
        case HS_R:
            PORTD &= ~(1 << PORTD4);
            break;
        case NS_G:
            PORTD &= ~(1 << PORTD5);
            break;
        case NS_Y:
            PORTD &= ~(1 << PORTD6);
            break;
        case NS_R:
            PORTD &= ~(1 << PORTD7);
            break;
        case FG_G:
            // No pin connected here
            break;
        case FG_R:
            // No pin connected here
            break;

        default:
            break;
    }
}

void LIGHT_Init() {
    // Set pins PD4-PD7 and  PB0-PB1 as output (as described in pinout.md)
    DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);  // As outputs
    DDRB |= (1 << DDB0) | (1 << DDB1);                              // As Outputs

    // Set pins PD2-PD3 as input (as described in pinout.md)
    DDRD &= ~((1 << DDD2) | (1 << DDD3));    // As Inputs
    PORTD |= (1 << PORTD2) | (1 << PORTD3);  // Pullups
    EICRA |= (1 << ISC01) | (1 << ISC11);    // Interrupt triggered by on falling edge
    EIMSK |= (1 << INT0) | (1 << INT1);      // Enable

    for (int i = 0; i < sizeof(lights) / sizeof(bool); i++) {
        off(i);
    }
    sei();
}

void LIGHT_debug() {
    USART_Transmit_s("| HS_G | HS_Y | HS_R | NS_G | NS_Y | NS_R | FG_G | FG_R |\n|");
    for (int i = 0; i < sizeof(lights) / sizeof(bool); i++) {
        lights[i] ? USART_Transmit_s(" on   |") : USART_Transmit_s(" off  |");
    }
    USART_Transmit('\n');
}

void LIGHT_HFOP_set_HS() {
    //* NS green phase -> FG red, NS yellow
    off(FG_G);
    on(FG_R);
    on(NS_Y);
    off(NS_G);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_NS_YELLOW);

    //* NS yellow -> NS yellow and red
    on(NS_R);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_NS_YELLOW_RED);

    //* NS yellow and red -> NS red, HS yellow
    off(NS_Y);
    off(HS_R);
    on(HS_Y);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_HS_YELLOW);

    //* HS yellow -> HS green
    off(HS_Y);
    on(HS_G);
    LIGHT_debug();
}

void LIGHT_HFOP_set_NS() {
    //* HS green phase -> HS yellow
    off(HS_G);
    on(HS_Y);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_HS_YELLOW);

    //* HS yellow -> HS yellow and red
    on(HS_R);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_HS_YELLOW_RED);

    //* HS yellow and red -> HS red, NS yellow
    off(HS_Y);
    off(NS_R);
    on(NS_Y);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_NS_YELLOW_TO_GREEN);

    //* NS yellow -> FG green
    on(FG_G);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_FG_GREEN);

    //* NS yellow -> NS green
    off(NS_Y);
    on(NS_G);
}

extern void LIGHT_LFOP_pause_timer_callback();
void LIGHT_LFOP_on_timer_callback() {
    if (freq_op == STATE_LOW_FREQ_OP) {
        TIMER_Cancel(TIMER_TRAFFIC_LIGHT);
        on(NS_Y);
        TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_LFOP_BLINK_ON, LIGHT_LFOP_pause_timer_callback);
        TIMER_Start(TIMER_TRAFFIC_LIGHT);
    }
}

void LIGHT_LFOP_pause_timer_callback() {
    USART_Transmit_s("Blink!\n");
    if (freq_op == STATE_LOW_FREQ_OP) {
        TIMER_Cancel(TIMER_TRAFFIC_LIGHT);
        off(NS_Y);
        TIMER_Declare(TIMER_TRAFFIC_LIGHT, (uint32_t)TIME_LFOP_BLINK_PAUSE, LIGHT_LFOP_on_timer_callback);
        TIMER_Start(TIMER_TRAFFIC_LIGHT);
    }
}

void LIGHT_LFOP() {
    TIMER_Cancel(TIMER_TRAFFIC_LIGHT);
    for (int i = 0; i < sizeof(lights) / sizeof(bool); i++) {
        off(i);
    }
    LIGHT_LFOP_on_timer_callback();
}
