#pragma once
//#include "I2Cbus.hpp"
#include <I2C.h>
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
    void sensorRead(std::string * humidityValue, std::string * temperatureValue);


    void ReadI2C(uint8_t* buffer, CMDData * data);
    void ConfigureCMD(CMDData * data, uint8_t* buffer, const int output_len);
};