#include <events.h>
#include <leitsystem_config.h>
#include <spi.h>
#include <uart.h>

void set_freq_op(freq_op_t freq) {
    SPI_select_SS();
    SPI_MasterTransmit(freq_op_to_spi_command(freq));
    SPI_deselect_SS();
}

void set_freq_op_if_changed(freq_op_t target) {
    static freq_op_t now = STATE_UNKNOWN;
    if (now != target) {
        // print changed state to USART
        USART_Transmit_s("Changing state from ");
        USART_Transmit_s(freq_op_to_string(now));
        USART_Transmit_s(" to ");
        USART_Transmit_s(freq_op_to_string(target));
        USART_Transmit('\n');
        now = target;
        set_freq_op(now);
    }
}

//todo read from RTC
uint8_t hours = 0;
day_t day = DAY_UNKNOWN;

void check_freq_op() {
    switch (day) {
        case DAY_MONDAY:
        case DAY_TUESDAY:
        case DAY_WEDNESDAY:
        case DAY_THURSDAY:
        case DAY_FRIDAY:
            if (hours < 5)
                set_freq_op_if_changed(STATE_REMOTE_FREQ_OP);  // 0 bis 5 Uhr
            else if (hours < 20)
                set_freq_op_if_changed(STATE_HIGH_FREQ_OP);  // 5 bis 20 Uhr
            else
                set_freq_op_if_changed(STATE_LOW_FREQ_OP);  // 20 bis 24 Uhr
            break;

        case DAY_SATURDAY:
            if (hours < 5)
                set_freq_op_if_changed(STATE_REMOTE_FREQ_OP);  // 0 bis 5 Uhr
            else if (hours < 9)
                set_freq_op_if_changed(STATE_LOW_FREQ_OP);  // 5 bis 9 Uhr
            else if (hours < 22)
                set_freq_op_if_changed(STATE_HIGH_FREQ_OP);  // 9 bis 22 Uhr
            else
                set_freq_op_if_changed(STATE_LOW_FREQ_OP);  // 22 bis 24 Uhr
            break;

        case DAY_SUNDAY:
            if (hours < 9)
                set_freq_op_if_changed(STATE_REMOTE_FREQ_OP);  // 0 bis 9 Uhr
            else if (hours < 13)
                set_freq_op_if_changed(STATE_LOW_FREQ_OP);  // 9 bis 13 Uhr
            else if (hours < 22)
                set_freq_op_if_changed(STATE_HIGH_FREQ_OP);  // 13 bis 22 Uhr
            else
                set_freq_op_if_changed(STATE_LOW_FREQ_OP);  // 22 bis 24 Uhr
            break;
        default:
            set_freq_op_if_changed(STATE_REMOTE_FREQ_OP);
            break;
    }
}

void SPI_check_error_code() {
    SPI_select_SS();
    SPI_MasterTransmit(Q_ERROR_CODE);
    error_t error = SPI_MasterTransmit(0x00);
    SPI_deselect_SS();
    if (error != ERROR_NO_ERROR) {
        USART_Transmit_s("Error code: ");
        USART_Transmit_s(error_to_string(error));
        USART_Transmit_s(" (");
        USART_Transmit_int64(0x0);
        USART_Transmit_s(")\n");
    }
}

uint8_t SPI_check_system_id() {
    SPI_select_SS();
    SPI_MasterTransmit(Q_SYSTEM_ID);
    uint8_t system_id = SPI_MasterTransmit(0x00);
    SPI_deselect_SS();
    return system_id;
}

void setup() {
    USART_Init(BAUDRATE);
    USART_Transmit_s("\n\nCompile time: ");
    USART_Transmit_s(__DATE__);
    USART_Transmit(' ');
    USART_Transmit_s(__TIME__);
    USART_Transmit_s("\nLEITSYSTEM v0.1\n\n");
    USART_Transmit_int64(0x0);

    SPI_MasterInit();
}

void loop() {
    check_freq_op();
    SPI_check_error_code();
    _delay_ms(1000);
}

int main() {
    setup();
    while (1)
        loop();
    return 0;
}
