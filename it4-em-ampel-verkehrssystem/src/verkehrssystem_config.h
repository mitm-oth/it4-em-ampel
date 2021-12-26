#ifndef __VERKEHRSSYSTEM_CONFIG_H_
#define __VERKEHRSSYSTEM_CONFIG_H_

#include "events.h"
#include "timer.h"

//** Events  (one hot)
//*  Zustände der Ampel
#define EVENT_HS_GRUEN ((event_t)(1 << 0))  // Hauptstraße hat grün
#define EVENT_NS_GRUEN ((event_t)(1 << 1))  // Nebenstraße und Fußgänger haben grün

//*  Timer events
#define EVENT_HS_TIMER_TICK ((event_t)(1 << 2))  // Hauptstraße hatte für best. Zeit grün
#define EVENT_NS_TIMER_TICK ((event_t)(1 << 3))  // Nebenstraße und Fußgänger hatten für best. Zeit grün

//*  Events
#define EVENT_FG_EVENT ((event_t)(1 << 4))  // Fußgänger drückt Knopf
#define EVENT_NS_EVENT ((event_t)(1 << 5))  // Auto fährt auf Induktionsplatte

//** Timer (0 - 7)
#define TIMER_TRAFFIC_LIGHT ((timer_t)0)  // Timer for current light phase

//** Times
//*  High frequency operation
#define TIME_HFOP_HS_GREEN_PHASE 5000  //[ms]
#define TIME_HFOP_NS_GREEN_PHASE 2000  //[ms]
#define TIME_HFOP_NS_YELLOW 100        //[ms]
#define TIME_HFOP_NS_YELLOW_RED 100    //[ms]
#define TIME_HFOP_HS_YELLOW 100        //[ms]

#define TIME_HFOP_HS_YELLOW 100      //[ms]
#define TIME_HFOP_HS_YELLOW_RED 100  //[ms]
#define TIME_HFOP_NS_YELLOW 50       //[ms]
#define TIME_HFOP_FG_GREEN 50        //[ms]
//// #define TIME_LOW_FREQ_OP_HS 1          //todo
//// #define TIME_LOW_FREQ_OP_NS 1          //todo
//// #define TIME_DEGRADED_OP_HS 1          //todo
//// #define TIME_DEGRADED_OP_HS 1          //todo

#endif  // __VERKEHRSSYSTEM_CONFIG_H_