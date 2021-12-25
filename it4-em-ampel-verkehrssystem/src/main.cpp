#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "timer.h"
#include "uart.h"
#include "verkehrssystem_config.h"

volatile uint32_t ns_time = 0;  // (in 10^-6 s) depends on Freq op
volatile uint32_t hs_time = 0;  // (in 10^-6 s) depends on Freq op
volatile uint8_t traffic_light_state = HS_GRUEN;

void set_traffic_lights_HS() {
}

void set_traffic_lights_NS() {
}

void HS_timer_callback() {
    set_event(HS_GRUEN);
}

void NS_timer_callback() {
    set_event(NS_GRUEN);
}

void setup() {
    //todo set ns_time, hs_time
    //todo init
    setupTimers();
}

void loop() {
    switch (traffic_light_state) {
        case HS_GRUEN:
            if (event_is_set(HS_TIMER_TICK) && (event_is_set(FG_EVENT) || event_is_set)) {  // switch to NS traffic now
                traffic_light_state = NS_GRUEN;
                declareTimer(TRAFFIC_LIGHT, ns_time, NS_timer_callback);
                startTimer(TRAFFIC_LIGHT);
                set_traffic_lights_NS();
            }
            break;
        case NS_GRUEN:
            if (event_is_set(NS_TIMER_TICK)) {  // switch to HS traffic now
                traffic_light_state = HS_GRUEN;
                declareTimer(TRAFFIC_LIGHT, hs_time, NS_timer_callback);
                startTimer(TRAFFIC_LIGHT);
                set_traffic_lights_HS();
            }
        default:
            break;
    }
}