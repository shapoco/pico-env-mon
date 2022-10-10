#ifndef MHZ19C_HPP
#define MHZ19C_HPP

#include "stdint.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"

class MHZ19C {
public:
    uart_inst_t * const uart;
    const int pin_tx;
    const int pin_rx;

    MHZ19C(uart_inst_t * uart, int pin_tx, int pin_rx) :
        uart(uart), pin_tx(pin_tx), pin_rx(pin_rx)
    { }

    void init() {
        uart_init(uart, 9600);
        gpio_set_function(pin_tx, GPIO_FUNC_UART);
        gpio_set_function(pin_rx, GPIO_FUNC_UART);

        // disable auto calibration
        uint8_t cmd[] = {0xFF, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86};
        uint8_t resp[9];
        uart_write_blocking(uart, cmd, 9);
        sleep_ms(100);
        while (uart_is_readable(uart)){
            uart_read_blocking(uart, resp, 1);
        }
        sleep_ms(100);
        
        // dummy read
        int dummy;
        measure(&dummy);
    }

    bool measure(int *result) {
        uint8_t cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
        uint8_t resp[9];
        uart_write_blocking(uart, cmd, 9);
        uart_read_blocking(uart, resp, 9);

        if (resp[0] == 0xff && resp[1] == 0x86) {
            *result = resp[2] * 256 + resp[3];
            return true;
        }
        else {
            *result = -1;
            return false;
        }
    }
};

#endif
