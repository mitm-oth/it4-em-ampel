#include "events.h"

//** Events  (one hot)
//* Zustände der Ampel
#define HS_GRUEN ((event_type)(1 << 0))  // Hauptstraße hat grün
#define NS_GRUEN ((event_type)(1 << 1))  // Nebenstraße und Fußgänger haben grün

//* Timer events
#define HS_TIMER_TICK ((event_type)(1 << 2))  // Hauptstraße hatte für best. Zeit grün
#define NS_TIMER_TICK ((event_type)(1 << 3))  // Nebenstraße und Fußgänger hatten für best. Zeit grün

//* Events
#define FG_EVENT ((event_type)(1 << 4))  // Fußgänger drückt Knopf
#define NS_EVENT ((event_type)(1 << 5))  // Auto fährt auf Induktionsplatte

//** Timer (0 - 7)
#define TRAFFIC_LIGHT 0  // Timer for current phase