#pragma once

#include <stdint.h>

//* Betriebszustände des Ampelsystems
typedef uint8_t freq_op_t;
#define STATE_HIGH_FREQ_OP ((freq_op_t)0x00)
#define STATE_LOW_FREQ_OP ((freq_op_t)0x01)
#define STATE_REMOTE_FREQ_OP ((freq_op_t)0x02)  // Lights switched off
#define STATE_DEGRADED_OP ((freq_op_t)0x03)
#define STATE_UNKNOWN ((freq_op_t)0xFF)

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
typedef uint8_t spi_command_t;
#define C_SW_STATE_HFOP (spi_command_t)0x01  // Switch state to Hight frequency op
#define C_SW_STATE_LFOP (spi_command_t)0x02  // Switch state to Low frequcy op
#define C_SW_STATE_RMOP (spi_command_t)0x03  // Switch state to Remote frequcy op
#define C_SW_STATE_DGOP (spi_command_t)0x04  // Switch state to Degraded frequcy op

#define Q_SYSTEM_ID (spi_command_t)0xFD   // Query system id
#define Q_ERROR_CODE (spi_command_t)0xFE  // Ask for system error code

//* Type conversions
//todo: bad practice maybe: inline is only optional; leads to linking errors if same function is in 2 objectfiles included
inline freq_op_t spi_command_to_freq_op(spi_command_t command) {
    switch (command) {
        case C_SW_STATE_HFOP:
            return STATE_HIGH_FREQ_OP;
        case C_SW_STATE_LFOP:
            return STATE_LOW_FREQ_OP;
        case C_SW_STATE_RMOP:
            return STATE_REMOTE_FREQ_OP;
        case C_SW_STATE_DGOP:
            return STATE_DEGRADED_OP;
        default:
            return STATE_REMOTE_FREQ_OP;
    }
}

//todo: bad practice maybe: inline is only optional; leads to linking errors if same function is in 2 objectfiles included
inline spi_command_t freq_op_to_spi_command(freq_op_t freq_op) {
    switch (freq_op) {
        case STATE_HIGH_FREQ_OP:
            return C_SW_STATE_HFOP;
        case STATE_LOW_FREQ_OP:
            return C_SW_STATE_LFOP;
        case STATE_REMOTE_FREQ_OP:
            return C_SW_STATE_RMOP;
        case STATE_DEGRADED_OP:
            return C_SW_STATE_DGOP;
        default:
            return C_SW_STATE_DGOP;
    }
}

//todo: bad practice maybe: inline is only optional; leads to linking errors if same function is in 2 objectfiles included
inline const char* freq_op_to_string(freq_op_t freq_op) {
    switch (freq_op) {
        case STATE_HIGH_FREQ_OP:
            return "STATE_HIGH_FREQ_OP";
        case STATE_LOW_FREQ_OP:
            return "STATE_LOW_FREQ_OP";
        case STATE_REMOTE_FREQ_OP:
            return "STATE_REMOTE_FREQ_OP";
        case STATE_DEGRADED_OP:
            return "STATE_DEGRADED_OP";
        default:
            return "STATE_NOT_DEFINED";
    }
}

inline const char* error_to_string(error_t error) {
    switch (error) {
        case ERROR_NO_ERROR:
            return "ERROR_NO_ERROR";
        case ERROR_RED_LIGHT_MR:
            return "ERROR_RED_LIGHT_MR";
        case ERROR_RED_LIGHT_SR:
            return "ERROR_RED_LIGHT_SR";
        case ERROR_RED_LIGHT_P:
            return "ERROR_RED_LIGHT_P";
        case ERROR_YELLOW_LIGHT_SR:
            return "ERROR_YELLOW_LIGHT_SR";
        case ERROR_FLASH_ERROR:
            return "ERROR_FLASH_ERROR";
        case ERROR_SRAM_ERROR:
            return "ERROR_SRAM_ERROR";
        case ERROR_STACK_ERROR:
            return "ERROR_STACK_ERROR";
        case ERROR_SW_ERROR:
            return "ERROR_SW_ERROR";
        case ERROR_TIME_ERROR:
            return "ERROR_TIME_ERROR";
        default:
            return "ERROR_UNKNOWN";
    }
}