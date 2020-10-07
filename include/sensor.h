#pragma once
#include "I2Cbus.hpp"
#include <string>

class sensor
{
public:
    /**
     * @brief Deze functie leest de waardes van de Si7021 sensor uit.
     * 
     * @param humidityValue Dit variabel geeft de luchtvochtigheid terug
     * @param temperatureValue Dit variabel geeft de temperatuur terug
     * 
     */
    void sensorRead(std::string humidityValue, std::string temperatureValue);
};