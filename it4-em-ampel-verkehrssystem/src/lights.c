#include "lights.h"

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

volatile bool lights[9] = {false};

void on(uint8_t light_pos) {
    lights[light_pos] = ON;
    //todo switch hardware lights
}

void off(uint8_t light_pos) {
    lights[light_pos] = OFF;
    //todo switch hardware lights
}

void LIGHT_debug() {
    USART_Transmit_s("| HS_G | HS_Y | HS_R | NS_G | NS_Y | NS_R | FG_G | FG_R |\n");
    for (int i = 0; i < sizeof(lights) / sizeof(bool); i++) {
        lights[i] ? USART_Transmit_s("| off|") : USART_Transmit_s("| on |");
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
    _delay_ms(TIME_HFOP_NS_YELLOW);

    //* NS yellow -> FG green
    on(FG_G);
    LIGHT_debug();
    _delay_ms(TIME_HFOP_FG_GREEN);

    //* NS yellow -> NS green
    off(NS_Y);
    on(NS_G);
}
