#pragma once

#include <stdint.h>

//* Betriebszustände des Ampelsystems
typedef uint8_t freq_op_t;
#define STATE_HIGH_FREQ_OP ((freq_op_t)0x00)
#define STATE_LOW_FREQ_OP ((freq_op_t)0x01)
#define STATE_REMOTE_FREQ_OP ((freq_op_t)0x02)  // Lights switched off
#define STATE_DEGRADED_OP ((freq_op_t)0x03)

//* Error codes
typedef uint8_t error_t;
#define ERROR_NO_ERROR ((error_t)0x00)
#define ERROR_RED_LIGHT_MR ((error_t)0x10)
#define ERROR_RED_LIGHT_SR ((error_t)0x11)
#define ERROR_RED_LIGHT_P ((error_t)0x12)
#define ERROR_YELLOW_LIGHT_SR ((error_t)0x13)
#define ERROR_FLASH_ERROR ((error_t)0x20)
#define ERROR_SRAM_ERROR ((error_t)0x21)
#define ERROR_STACK_ERROR ((error_t)0x22)
#define ERROR_SW_ERROR ((error_t)0x80)
#define ERROR_TIME_ERROR ((error_t)0x81)

//* Communication commands
#define C_SW_STATE_HFOP 0x01  // Switch state to Hight frequency op
#define C_SW_STATE_LFOP 0x02  // Switch state to Low frequcy op
#define C_SW_STATE_RMOP 0x03  // Switch state to Remote frequcy op
#define C_SW_STATE_DGOP 0x04  // Switch state to Degraded frequcy op

#define Q_ERROR_CODE 0xFE  // Ask for system error code
