#include "LIS3DE.h"

LIS3DE::LIS3DE(TwoWire& wire, uint8_t address): _wire(wire), _address(address)
{

}

int8_t LIS3DE::getTemperatureDelta()
{
    uint8_t originalReg4 = readRegister(LIS3DE::CTRL_REG4);
    writeRegister(LIS3DE::CTRL_REG4, 0b10000000); // BDU on
    
    readRegister(LIS3DE::OUT_ADC3_L); // low byte can be thrown away, but must be read!
    int8_t value = readRegister(LIS3DE::OUT_ADC3_H);
    
    writeRegister(LIS3DE::CTRL_REG4, originalReg4);
    
    return value;
}

void LIS3DE::enable(bool isLowPowerEnabled, ODR odr, Axes axes, bool isTemperatureOn)
{
    // set odr, mode, enabled axes
    writeRegister(LIS3DE::CTRL_REG1, (odr << 4) | (isLowPowerEnabled << 3) | axes);
    
    if (isTemperatureOn) {
        // enable aux ADC and temperature sensor
        writeRegister(LIS3DE::TEMP_CFG_REG, 0b11000000);
    }
    else {
        // disable aux ADC and temperature sensor
        writeRegister(LIS3DE::TEMP_CFG_REG, 0);
    }
}

void LIS3DE::disable()
{
    enable(true, LIS3DE::PowerDown, LIS3DE::NoAxis, false);
}

void LIS3DE::reboot()
{
    writeRegister(CTRL_REG5, 0b10000000);
}

uint8_t LIS3DE::readRegister(uint8_t reg)
{
    Wire.beginTransmission(_address);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    
    Wire.requestFrom(_address, 1);
    
    return Wire.read();
}

void LIS3DE::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission((uint8_t)_address);
    
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)value);
    
    Wire.endTransmission();
}
