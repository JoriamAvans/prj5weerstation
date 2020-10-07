#include "sensor.h"

#define DEVICE_ADDR 0x40
#define REG_ADDR_HUM 0xE5
#define REG_ADDR_TEMP 0xF3
#define LENGTH 2

void sensor::sensorRead(std::string humidityValue, std::string temperatureValue)
{
    uint8_t buffer[2];

    I2C_t myI2C(I2C_NUM_0);

    myI2C.begin(GPIO_NUM_21, GPIO_NUM_22);

    while (1)
    {
        //Humidity calculator
        myI2C.writeBit(DEVICE_ADDR, REG_ADDR_HUM, 2, 0);
        myI2C.readBytes(DEVICE_ADDR, REG_ADDR_HUM, LENGTH, buffer);

        printf("Buffers: %hhx, %hhx\n", buffer[0], buffer[1]);

        float humidity = ((buffer[0] * 256.0) + buffer[1]);
        humidity = ((125 * humidity) / 65536.0) - 6;
        printf("Humidity: %.2f\n", humidity);

        //Temperature calculator
        myI2C.writeBit(DEVICE_ADDR, REG_ADDR_TEMP, 2, 0);
        myI2C.readBytes(DEVICE_ADDR, REG_ADDR_TEMP, LENGTH, buffer);

        float temp = ((buffer[0] * 256.0) + buffer[1]);
        float celsTemp = ((175.72 * temp) / 65536.0) - 46.85;
        printf("Temperature: %.2f\n", celsTemp);
        //float to char array
        char temp2[8];
        sprintf(temp2, "%.2f", celsTemp);
        //char array to string
        temperatureValue = temp2;

        vTaskDelay(pdMS_TO_TICKS(100000));
    }
    myI2C.close();
}