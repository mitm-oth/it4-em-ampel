#ifndef __LIGHTS_H_
#define __LIGHTS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>  // Only for debug()

#include "uart.h"  // Only for debug()
#include "verkehrssystem_config.h"

void LIGHT_HFOP_set_HS();

void LIGHT_HFOP_set_NS();

void LIGHT_debug();

#endif  // __LIGHTS_H_