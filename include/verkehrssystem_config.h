#pragma once

#include "events/events.h"
#include "global_config.h"
#include "timer/timer.h"

extern volatile freq_op_t freq_op;
extern volatile error_t error_code;

//** Zustände der Ampel
#define STATE_HS_GRUEN (1 << 0)  // Hauptstraße hat grün
#define STATE_NS_GRUEN (1 << 1)  // Nebenstraße und Fußgänger haben grün

//** Events  (one hot)
//*  Timer events
#define EVENT_HS_TIMER_TICK ((event_t)(1 << 2))  // Hauptstraße hatte für best. Zeit grün
#define EVENT_NS_TIMER_TICK ((event_t)(1 << 3))  // Nebenstraße und Fußgänger hatten für best. Zeit grün

//*  Events
#define EVENT_FG_ARRIVED ((event_t)(1 << 4))  // Fußgänger drückt Knopf
#define EVENT_NS_ARRIVED ((event_t)(1 << 5))  // Auto fährt auf Induktionsplatte

//** Timer (0 - 7)
#define TIMER_TRAFFIC_LIGHT ((timer_t)0)  // Timer for current light phase

//** Times
//*  High frequency operation
//todo optimize times
#define TIME_HFOP_HS_GREEN_PHASE 7000  //[ms] todo 60s
#define TIME_HFOP_NS_GREEN_PHASE 7000  //[ms] todo 30s
#define TIME_HFOP_NS_YELLOW 150        //[ms]
#define TIME_HFOP_NS_YELLOW_RED 200    //[ms]
#define TIME_HFOP_HS_YELLOW 150        //[ms]

#define TIME_HFOP_HS_YELLOW 150           //[ms]
#define TIME_HFOP_HS_YELLOW_RED 200       //[ms]
#define TIME_HFOP_NS_YELLOW_TO_GREEN 100  //[ms]
#define TIME_HFOP_FG_GREEN 100            //[ms]

#define TIME_LFOP_BLINK_PAUSE 3000  //[ms]
#define TIME_LFOP_BLINK_ON 1000     //[ms]
