#include "sensor.h"

#define DEVICE_ADDR 0x15
#define REG_ADDR_HUM 0xF5
#define REG_ADDR_TEMP 0xF3
#define LENGTH 2

float* sensor::sensorRead(char* humidityValue, char* temperatureValue)
{
    uint8_t buffer[2];
    float results[2] = {0, 0};
    char size[6];
    // OR create an object which manages controller num 0
    I2C_t myI2C(I2C_NUM_0);
    // configure and initialize
    myI2C.begin(GPIO_NUM_21, GPIO_NUM_22);

    while(1){
    //humidity
    myI2C.writeBit(DEVICE_ADDR, REG_ADDR_HUM, 2, 0);
    myI2C.readBytes(DEVICE_ADDR, REG_ADDR_HUM, LENGTH, buffer);

    printf("Buffers: %hhx, %hhx\n", buffer[0], buffer[1]);

    float humidity = ((buffer[0] * 256.0) + buffer[1]);
    humidity = ((125 * humidity) / 65536.0) - 6;
    sprintf(humidityValue, "%.2f\n", humidity);
    //temperature

    myI2C.writeBit(DEVICE_ADDR, REG_ADDR_TEMP, 2, 0);
    myI2C.readBytes(DEVICE_ADDR, REG_ADDR_TEMP, LENGTH, buffer);

    float temp = ((buffer[0] * 256.0) + buffer[1]);
    float celsTemp = ((175.72 * temp) / 65536.0) - 46.85;
    sprintf(temperatureValue, "%.2f", celsTemp);
    

    vTaskDelay(pdMS_TO_TICKS(100000));}
    myI2C.close();
    return results;
}