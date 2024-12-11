#ifndef CO2_SENSOR_HPP
#define CO2_SENSOR_HPP

#include "hardware/uart.h"
#include "pico/stdlib.h"

class CO2Sensor {
public:
    enum SensorType {
        UNKNOWN = 0,    // Unknown or invalid sensor
        MH_Z19,         // Winsen MH-Z19 series NDIR CO2 sensor (MH-Z19B & MH-Z19C)
        SENSEAIR_S8     // Senseair S8 series NDIR CO2 sensor (Residential & Commercial & LP)
    };

    // Constructor
    CO2Sensor(uart_inst_t* uart, uint tx_pin, uint rx_pin, uint baud_rate = 9600);
    
    // Destructor
    ~CO2Sensor();
    
    // Initialisation
    bool init();

    // Configure ABC (Automatic Baseline Compensation), 0x00 = OFF
    bool ABC(uint8_t ABCstate);

    // Get CO2 reading from sensor in ppm using a pointer
    bool getCO2Reading(int* co2_ppm);

private:
    uart_inst_t* const _uart;
    const uint _tx_pin;
    const uint _rx_pin;
    const uint _baud_rate;
    SensorType _sensor;

    // Determines SensorType using detect functions, runs once in init()
    bool detectSensorType();
    
    // Checks if current sensor is this type
    bool detectMHZ19();
    bool detectSenseairS8();
    
    // Waits for sensor to start returning valid readings as to not add invalid data to trend graphs
    bool waitForWarmUp(uint8_t timeout_s);

    // Handles ABC configuration for each specific sensorType
    bool ABCMHZ19(uint8_t ABCvalue);
    bool ABCSenseairS8(uint8_t ABCvalue);

    // Handles CO2 measurement functions for each specific sensorType
    bool getMHZ19Reading(int* co2_ppm);
    bool getSenseairS8Reading(int* co2_ppm);
    
    // Use instead of uart_read_blocking to gracefully handle missing UART bytes
    bool uart_read_with_timeout(uart_inst_t *uart, uint8_t *buffer, uint8_t x, uint32_t timeout_us = 100000);
    
    // Discard content of UART buffer
    void uart_read_purge(uart_inst_t *uart);
};

#endif // CO2_SENSOR_HPP
