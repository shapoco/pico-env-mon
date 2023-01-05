#ifndef BME280_HPP
#define BME280_HPP

#include "stdint.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

class BME280 {

public:
    spi_inst_t * const spi;
    const int pin_csb;

    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6;

    int32_t t_fine;

    BME280(spi_inst_t *spi, int pin_csb) :
        spi(spi), pin_csb(pin_csb)
    { }

    void cs_select() {
        asm volatile("nop \n nop \n nop");
        gpio_put(pin_csb, 0);
        asm volatile("nop \n nop \n nop");
    }

    void cs_deselect() {
        asm volatile("nop \n nop \n nop");
        gpio_put(pin_csb, 1);
        asm volatile("nop \n nop \n nop");
    }

    void write_reg(uint8_t addr, uint8_t data) {
        uint8_t buff[2];
        buff[0] = addr & 0x7f;
        buff[1] = data;
        cs_select();
        spi_write_blocking(spi, buff, 2);
        cs_deselect();
        sleep_ms(10);
    }

    void read_reg(uint8_t addr, uint8_t *buff, uint16_t len) {
        addr |= 0x80;
        cs_select();
        spi_write_blocking(spi, &addr, 1);
        sleep_ms(10);
        spi_read_blocking(spi, 0, buff, len);
        cs_deselect();
        sleep_ms(10);
    }

    void init() {
        uint8_t buff[26];

        gpio_init(pin_csb);
        gpio_set_dir(pin_csb, GPIO_OUT);
        gpio_put(pin_csb, 1);
        sleep_ms(100);

        read_reg(0x88, buff, 26);

        dig_T1 = (uint16_t)buff[0] | ((uint16_t)buff[1] << 8);
        dig_T2 = (uint16_t)buff[2] | ((uint16_t)buff[3] << 8);
        dig_T3 = (uint16_t)buff[4] | ((uint16_t)buff[5] << 8);

        dig_P1 = (uint16_t)buff[6] | ((uint16_t)buff[7] << 8);
        dig_P2 = (uint16_t)buff[8] | ((uint16_t)buff[9] << 8);
        dig_P3 = (uint16_t)buff[10] | ((uint16_t)buff[11] << 8);
        dig_P4 = (uint16_t)buff[12] | ((uint16_t)buff[13] << 8);
        dig_P5 = (uint16_t)buff[14] | ((uint16_t)buff[15] << 8);
        dig_P6 = (uint16_t)buff[16] | ((uint16_t)buff[17] << 8);
        dig_P7 = (uint16_t)buff[18] | ((uint16_t)buff[19] << 8);
        dig_P8 = (uint16_t)buff[20] | ((uint16_t)buff[21] << 8);
        dig_P9 = (uint16_t)buff[22] | ((uint16_t)buff[23] << 8);

        dig_H1 = buff[25];

        read_reg(0xe1, buff, 7);

        dig_H2 = (uint16_t)buff[0] | ((uint16_t)buff[1] << 8);
        dig_H3 = (int8_t)buff[2];
        dig_H4 = ((uint16_t)buff[3] << 4) | (buff[4] & 0xf);
        dig_H5 = ((buff[4] >> 4) & 0xf) | ((uint16_t)buff[5] << 4);
        dig_H6 = (int8_t)buff[6];
            
        write_reg(0xf2, 0x1);
        write_reg(0xf4, 0x24);
    }

    int32_t compensate_T(int32_t adc_T)
    {
        int32_t var1, var2, T;
        var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
        var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) *
        ((int32_t)dig_T3)) >> 14;
        t_fine = var1 + var2;
        T = (t_fine * 5 + 128) >> 8;
        return T;
    }

    uint32_t compensate_P(int32_t adc_P)
    {
        int64_t var1, var2, p;
        var1 = ((int64_t)t_fine) - 128000;
        var2 = var1 * var1 * (int64_t)dig_P6;
        var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
        var2 = var2 + (((int64_t)dig_P4)<<35);
        var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
        var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
        if (var1 == 0)
        {
            return 0;
        }
        p = 1048576-adc_P;
        p = (((p<<31)-var2)*3125)/var1;
        var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
        var2 = (((int64_t)dig_P8) * p) >> 19;
        p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
        return (uint32_t)p;
    }

    uint32_t compensate_H(int32_t adc_H)
    {
        int32_t v_x1_u32r;
        v_x1_u32r = (t_fine - ((int32_t)76800));
        v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) +
        ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r *
        ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
        ((int32_t)dig_H2) + 8192) >> 14));
        v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
        v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
        v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
        return (uint32_t)(v_x1_u32r>>12);
    }
    
    void read_raw(int32_t *temperature, int32_t *humidity, int32_t *pressure) {
        uint8_t buff[8];
        write_reg(0xf4, 0x25);
        sleep_ms(20);
        read_reg(0xf7, buff, 8);
        *pressure = ((uint32_t) buff[0] << 12) | ((uint32_t) buff[1] << 4) | (buff[2] >> 4);
        *temperature = ((uint32_t) buff[3] << 12) | ((uint32_t) buff[4] << 4) | (buff[5] >> 4);
        *humidity = (uint32_t) buff[6] << 8 | buff[7];
    }

    void read_env(float *temperature, float *humidity, float *pressure) {
        int32_t h, p, t;
        read_raw(&t, &h, &p);
        *temperature = compensate_T(t) / 100.0f;
        *pressure = compensate_P(p) / 25600.0f;
        *humidity = compensate_H(h) / 1024.0f;
    }
};

#endif
