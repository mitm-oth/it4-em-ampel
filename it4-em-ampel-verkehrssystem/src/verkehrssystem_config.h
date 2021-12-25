//** Events
//* Zustände der Ampel (one hot)
#define HS_GRUEN (1 << 0)  // Hauptstraße hat grün
#define NS_GRUEN (1 <<)    // Nebenstraße und Fußgänger haben grün

//* Timer events (one hot)
#define HS_TIMER_TICK (1 << 0)  // Hauptstraße hatte für best. Zeit grün
#define NS_TIMER_TICK (1 << 1)  // Nebenstraße und Fußgänger hatten für best. Zeit grün

//* Events (one hot)
#define FG_EVENT (1 << 0)  // Fußgänger drückt Knopf
#define NS_EVENT (1 << 1)  // Auto fährt auf Induktionsplatte

//** Timer (one hot)
#define TRAFFIC_LIGHT (1 << 0)  // Timer for current phase