#include "global_config.h"

freq_op_t spi_command_to_freq_op(spi_command_t command) {
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

spi_command_t freq_op_to_spi_command(freq_op_t freq_op){
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
const char* freq_op_to_string(freq_op_t freq_op){
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

const char* error_to_string(error_t error){
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