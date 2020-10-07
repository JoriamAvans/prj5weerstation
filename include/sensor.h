#pragma once
#include <I2Cbus.hpp>

class sensor{
    public:
    float* sensorRead(char* humidityValue, char* temperatureValue);
};