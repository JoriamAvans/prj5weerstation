#pragma once
#include "I2Cbus.hpp"
#include <string>

class sensor{
    public:
    void sensorRead(std::string humidityValue, std::string temperatureValue);
};