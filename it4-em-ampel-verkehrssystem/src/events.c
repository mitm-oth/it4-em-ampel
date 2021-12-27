#include "events.h"

volatile event_t events = 0x0000;

void EVENT_set(event_t event) {
    cli();  //todo save status reg
    events |= event;
    sei();  //todo write back
}

void EVENT_clear(event_t event) {
    cli();  //todo save status reg
    events &= ~(event);
    sei();  //todo write back
}

bool EVENT_is_set(event_t event) {
    return (events & event);
}

void EVENT_debug() {
    char buffer[30] = "";
    sprintf(buffer, "Events: %#06x\n", events);
    USART_Transmit_s(buffer);
}