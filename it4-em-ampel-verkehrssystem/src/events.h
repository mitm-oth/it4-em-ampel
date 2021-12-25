#include <stdbool.h>
#include <stdint.h>

typedef uint16_t event_type;  //todo change to 8 Bit if possible

void set_event(event_type event);
void clear_event(event_type event);

bool event_is_set(event_type event);
