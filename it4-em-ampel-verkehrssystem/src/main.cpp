#include "verkehrssystem_config.h"
#include

volatile uint16_t ns_time = 0;  // depends on Freq op
volatile uint16_t hs_time = 0;  // depends on Freq op

void setup() {
    //todo set ns_time, hs_time
}

void loop() {
    switch (traffic_light_state) {
        case HS_GRUEN:
            if (event_occured(HS_TIMER_TICK) && (event_occured(FG_EVENT) || event_occured)) {  // switch to NS traffic now
                traffic_light_state = NS_GRUEN;
                start_timer(TRAFFIC_LIGHT, ns_time);
                set_traffic_light(NS_GRUEN);
            }
            break;
        case NS_GRUEN:
            if (event_occured(NS_TIMER_TICK)) {  // switch to HS traffic now
                traffic_light_state = HS_GRUEN;
                start_timer(TRAFFIC_LIGHT, hs_time);
                set_traffic_light(HS_GRUEN);
            }
        default:
            break;
    }
    else if (event_occured(NS_GRUEN)) {
    }
}