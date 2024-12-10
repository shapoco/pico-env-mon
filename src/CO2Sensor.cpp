#include "CO2Sensor.hpp"

CO2Sensor::CO2Sensor(uart_inst_t* uart, uint tx_pin, uint rx_pin, uint baud_rate)
    : _uart(uart), _tx_pin(tx_pin), _rx_pin(rx_pin), _baud_rate(baud_rate), _sensor(UNKNOWN) {
}

CO2Sensor::~CO2Sensor() {
    uart_deinit(_uart);
}

bool CO2Sensor::init() {
    uart_init(_uart, 9600);
    gpio_set_function(_tx_pin, GPIO_FUNC_UART);
    gpio_set_function(_rx_pin, GPIO_FUNC_UART);
    
    if (detectSensorType() && waitForWarmUp(10)) {
        return true; // Initialisation successful
    }
    return false;
}

bool CO2Sensor::detectSensorType() {
    for (int i = 0; i < 5; i++) {
        sleep_ms(1000); // Wait for sensor to be ready
        
        uart_read_purge(_uart);
        
        if (detectMHZ19()) {
            _sensor = MH_Z19;
            return true;
        } 
        else if (detectSenseairS8()) {
            _sensor = SENSEAIR_S8;
            return true;
        } 
    }
    
    _sensor = UNKNOWN;
    return false;

}

bool CO2Sensor::waitForWarmUp(uint8_t timeout_s) {  
    // Senseair S8 reads 0 ppm for the first couple seconds, wait till it reads > 0 ppm
    // MH-Z19 reads factory baseline 410 ppm for the first couple seconds, but can't reliably avoid this
    
    int co2_ppm = -1; 
    
    for (int i = 0; i < timeout_s; i++) {
        sleep_ms(1000);
        
        uart_read_purge(_uart);
        
        if (getCO2Reading(&co2_ppm)) {
            if (co2_ppm > 10) {
                return true;
            }
        }
    }
    return false;
}

bool CO2Sensor::ABC(uint8_t ABCvalue) {
    if (_sensor == MH_Z19) {
        return ABCMHZ19(ABCvalue);
    } 
    else if (_sensor == SENSEAIR_S8) {
        return ABCSenseairS8(ABCvalue);
    } 
    else {
        return false;  // Unknown or invalid sensor type
    }
}

bool CO2Sensor::ABCMHZ19(uint8_t ABCvalue) {
    uint8_t cmd[] = {0xFF, 0x01, 0x79, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xE6}; // Enable ABC with default period
    uint8_t resp[9];
    
    if (ABCvalue == 0x00) {
        cmd[3] = 0x00; // ABC value (0x00 = disabled)
        cmd[8] = 0x86; // Custom checksum, add all bytes then 0xFF-result
    }
    
    uart_write_blocking(_uart, cmd, sizeof(cmd));
    
    sleep_ms(100);
    uart_read_purge(_uart);
    sleep_ms(100);
    
    
    return true; // Assumed successful.
}

bool CO2Sensor::ABCSenseairS8(uint8_t ABCvalue) {
    uint8_t cmd[] = {0xFE, 0x06, 0x00, 0x1F, 0x00, 0xB4, 0xAC, 0x74}; // Enable ABC with default 7.5 day period
    
    if (ABCvalue == 0x00) {
        // TODO: Allow for arbitrary ABC values, not just default 0xB4 (
        cmd[5] = 0X00; // ABC value
        cmd[6] = 0XAC; // Checksum lower (CRC-16/MODBUS)
        cmd[7] = 0X03; // Checksum upper
    }

    uint8_t resp[sizeof(cmd)];

    uart_write_blocking(_uart, cmd, sizeof(cmd));
    
    if (uart_read_with_timeout(_uart, resp, sizeof(resp))) {
        if (resp == cmd) {
            return true; // ABC configuration successful.
        }
        else {
            return false; // ABC configuration failed. Response ID was invalid.
        }
    }
    else {
        return false; // ABC configuration failed. Timed out trying to read UART response.
    }
}

bool CO2Sensor::detectMHZ19() {
    // Winsen devices don't appear to have a device/type ID, just check for valid reading instead
    int co2_ppm = -1; 
    
    if (getMHZ19Reading(&co2_ppm)) {
        if (co2_ppm >= 0 && co2_ppm <= 10000) {
            return true;
        }
    }
    return false;
}

bool CO2Sensor::detectSenseairS8() {
    // TODO: Check device ID using either IR26/IR27 Type ID or IR30/IR31 Sensor ID
    int co2_ppm = -1; 
    
    if (getSenseairS8Reading(&co2_ppm)) {
        if (co2_ppm >= 0 && co2_ppm <= 10000) {
            return true;
        }
    }
    return false;
}

bool CO2Sensor::getCO2Reading(int* co2_ppm) {
    if (co2_ppm == nullptr) {
        *co2_ppm = -1;
        return false;  // Pointer is invalid
    }

    if (_sensor == MH_Z19) {
        return getMHZ19Reading(co2_ppm);
    } 
    else if (_sensor == SENSEAIR_S8) {
        return getSenseairS8Reading(co2_ppm);
    } 
    else {
        *co2_ppm = -1;
        return false;  // Unknown or invalid sensor type
    }
}

bool CO2Sensor::getMHZ19Reading(int* co2_ppm) {
    uint8_t cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // for Winsen MH-Z19
    uint8_t resp[9];
    
    uart_read_purge(_uart);
    
    uart_write_blocking(_uart, cmd, sizeof(cmd));
    sleep_ms(50);
    
    if (uart_read_with_timeout(_uart, resp, sizeof(resp))) {
        if (resp[0] == 0xFF && resp[1] == 0x86) {
            *co2_ppm = (resp[2] << 8) | resp[3];
            // TODO: Add checksum logic
            return true; // Reading successful.
        }
        else {
            return false; // Reading failed. Response ID was invalid.
        }
    }
    else {
        return false; // Reading failed. Timed out trying to read UART response.
    }
}

bool CO2Sensor::getSenseairS8Reading(int *co2_ppm) {
    uint8_t cmd[] = {0xFE, 0X04, 0X00, 0X03, 0X00, 0X01, 0XD5, 0XC5}; // for Senseair S8 LP
    uint8_t resp[7];
    
    uart_read_purge(_uart);
    
    uart_write_blocking(_uart, cmd, sizeof(cmd));
    sleep_ms(50);
    
    if (uart_read_with_timeout(_uart, resp, sizeof(resp))) {
        if (resp[0] == 0xFE && resp[1] == 0x04) {
            *co2_ppm = (resp[3] << 8) | resp[4];
            // TODO: Add checksum logic
            return true; // Reading successful.
        }
        else {
            return false; // Reading failed. Response ID was invalid.
        }
    }
    else {
        return false; // Reading failed. Timed out trying to read UART response.
    }
}

bool CO2Sensor::uart_read_with_timeout(uart_inst_t *uart, uint8_t *buffer, uint8_t bytes, uint32_t timeout_us) {
    uint32_t start_time = time_us_32();

    for (int i = 0; i < bytes; i++) {
        if (time_us_32() - start_time > timeout_us) {
            return false; // Read failed. Timeout expired.
        }

        if (uart_is_readable(uart)) {
            buffer[i] = uart_getc(uart);
        } else {
            i--;  // Decrement i to retry reading this byte
        }
    }

    return true;  // Successfully read all bytes within the timeout
}

void CO2Sensor::uart_read_purge(uart_inst_t *uart) {
    // Discard bytes in UART buffer until empty
    uint8_t dummy = 0;
    while (uart_is_readable(uart)) {
        uart_read_blocking(uart, &dummy, 1);
    }
}
