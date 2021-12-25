//* Zustände der Ampel
#define HAUPTSTRASSE_GRUEN 0x00
#define NEBENSTRASSE_GRUEN 0x01

//* Timer events (one hot)
#define HS_TIMER_TICK (1 << 0)  // Hauptstraße hatte für best. Zeit grün
#define NS_TIMER_TICK (1 << 1)  // Nebenstraße hatte für best. Zeit grün

//* Events
#define FG_EVENT 0x00  // Fußgänger drückt Knopf
#define NS_EVENT 0x00  // Auto fährt auf Induktionsplatte
