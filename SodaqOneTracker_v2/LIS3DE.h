#ifndef LIS3DE_H_
#define LIS3DE_H_

#include "Arduino.h"
#include <Wire.h>

#define LIS3DE_ADDRESS 0b0101000
#define LIS3DE_DEFAULT_TEMPERATURE_OFFSET 20

class LIS3DE
{
    public:
    
        enum Register {
            STATUS_REG_AUX = 0x07,
            OUT_ADC1_L = 0x08,
            OUT_ADC1_H = 0x09,
            OUT_ADC2_L = 0x0A,
            OUT_ADC2_H = 0x0B,
            OUT_ADC3_L = 0x0C,
            OUT_ADC3_H = 0x0D,
            INT_COUNTER_REG = 0x0E,
            WHO_AM_I = 0x0F,
            TEMP_CFG_REG = 0x1F,
            CTRL_REG1 = 0x20,
            CTRL_REG2 = 0x21,
            CTRL_REG3 = 0x22,
            CTRL_REG4 = 0x23,
            CTRL_REG5 = 0x24,
            CTRL_REG6 = 0x25,
            REFERENCE = 0x26,
            STATUS_REG2 = 0x27,
            OUT_X = 0x29,
            OUT_Y = 0x2B,
            OUT_Z = 0x2D,
            FIFO_CTRL_REG = 0x2E,
            FIFO_SRC_REG = 0x2F,
            IG1_CFG = 0x30,
            IG1_SOURCE = 0x31,
            IG1_THS = 0x32,
            IG1_DURATION = 0x33,
            IG2_CFG = 0x34,
            IG2_SOURCE = 0x35,
            IG2_THS = 0x36,
            IG2_DURATION = 0x37,
            CLICK_CFG = 0x38,
            CLICK_SRC = 0x39,
            CLICK_THS = 0x3A,
            TIME_LIMIT = 0x3B,
            TIME_LATENCY = 0x3C,
            TIME_WINDOW = 0x3D,
            ACT_THS = 0x3E,
            ACT_DUR = 0x3F
        };
        
        enum ODR {
            PowerDown = 0b000,
            NormalLowPower1Hz = 0b0001,
            NormalLowPower10Hz = 0b0010,
            NormalLowPower25Hz = 0b0011,
            NormalLowPower50Hz = 0b0100,
            NormalLowPower100Hz = 0b0101,
            NormalLowPower200Hz = 0b0110,
            NormalLowPower400Hz = 0b0111,
            LowPower1k6Hz = 0b1000,
            Normal1k344LowPower5k376Hz = 0b1001
        };
        
        enum Axes {
            NoAxis = 0,
            X = 0b001,
            Y = 0b010,
            Z = 0b100,
            AllAxes = X | Y | Z
        };
        
        LIS3DE(TwoWire& wire = Wire, uint8_t address = LIS3DE_ADDRESS);
        int8_t getTemperature(uint8_t temperatureOffset = LIS3DE_DEFAULT_TEMPERATURE_OFFSET);
        void enable(bool isLowPowerEnabled = false, ODR odr = NormalLowPower1Hz, Axes axes = AllAxes, bool isTemperatureOn = true);
        void disable();
    private:
        TwoWire& _wire;
        uint8_t _address;
        
        uint8_t readRegister(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t value);
};

#endif

