#ifndef CO2_SENSOR_HPP
#define CO2_SENSOR_HPP

#include "hardware/uart.h"
#include "pico/stdlib.h"

class CO2Sensor {
public:
    enum SensorType {
        UNKNOWN = 0,    // Unknown or invalid sensor
        WINSEN_MH_Z,    // Winsen MH-Z series NDIR CO2 sensor (MH-Z19B/C/D & MH-Z14A & MH-Z1311A)
        SENSEAIR_S8,    // Senseair S8 series NDIR CO2 sensor (Residential & Commercial & LP)
        GUANGZHOU_HC8   // 广州海谷电子科技有限公司 (Guangzhou Haigu Electronic Technology Co., Ltd.) NDIR CO2 sensor (PCB marked "CO2-C8 V4")
    };

    // Constructor
    CO2Sensor(uart_inst_t* uart, uint tx_pin, uint rx_pin, uint baud_rate = 9600);
    
    // Destructor
    ~CO2Sensor();
    
    // Initialisation
    bool init();

    // Configure ABC (Automatic Baseline Compensation), 0x00 = OFF
    bool setABC(uint8_t ABCstate);

    // Get CO2 reading from sensor in ppm using a pointer
    bool getCO2ppm(int* co2_ppm);

private:
    uart_inst_t* const _uart;
    const uint _tx_pin;
    const uint _rx_pin;
    const uint _baud_rate;
    SensorType _sensor;

    // Determines SensorType using detect functions, runs once in init()
    bool detectSensorType();
    
    // Checks if current sensor is this type
    bool detectWINSEN_MH_Z();
    bool detectSENSEAIR_S8();
    bool detectGUANGZHOU_HC8();
    
    // Waits for sensor to start returning valid readings as to not add invalid data to trend graphs
    bool waitForWarmUp(uint8_t timeout_s);

    // Handles ABC configuration for each specific sensorType
    bool setABCWINSEN_MH_Z(uint8_t ABCvalue);
    bool setABCSENSEAIR_S8(uint8_t ABCvalue);
    bool setABCGUANGZHOU_HC8(uint8_t ABCvalue);

    // Handles CO2 measurement functions for each specific sensorType
    bool getWINSEN_MH_ZCO2ppm(int* co2_ppm);
    bool getSENSEAIR_S8CO2ppm(int* co2_ppm);
    bool getGUANGZHOU_HC8ppm(int* co2_ppm);
    
    // Use instead of uart_read_blocking to gracefully handle missing UART bytes
    bool uart_read_with_timeout(uart_inst_t *uart, uint8_t *buffer, uint8_t x, uint32_t timeout_us = 100000);
    
    // Discard content of UART buffer
    void uart_read_purge(uart_inst_t *uart);
};

#endif // CO2_SENSOR_HPP
