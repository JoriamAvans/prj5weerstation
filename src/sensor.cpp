#include "sensor.h"

#define DEVICE_ADDR 0x40
#define REG_ADDR_HUM 0xE5
#define REG_ADDR_TEMP 0xF3
#define LENGTH 2

I2C myI2C;

void sensor::ReadI2C(uint8_t *buffer, CMDData *data)
{
    ConfigureCMD(data, buffer, 2);

    myI2C.WriteCmd(data);
    vTaskDelay(100 / portTICK_RATE_MS);
    myI2C.ReadCmd(data);
}

void sensor::ConfigureCMD(CMDData *data, uint8_t *buffer, const int output_len)
{
    data->Address = DEVICE_ADDR;
    data->Buffer = (uint8_t *)buffer;
    data->Len = sizeof(data) / sizeof(uint8_t);

    data->OutputBuffer = (uint8_t *)calloc(output_len, sizeof(uint8_t));
    data->OutputLen = output_len;
}

void sensor::sensorRead(std::string * humidityValue, std::string * temperatureValue)
{
    //I2C_t myI2C(I2C_NUM_0);

    //myI2C.begin(GPIO_NUM_21, GPIO_NUM_22);

    //Humidity calculator
    //myI2C.writeBit(DEVICE_ADDR, REG_ADDR_HUM, 2, 0);
    //myI2C.readBytes(DEVICE_ADDR, REG_ADDR_HUM, LENGTH, buffer);

    CMDData data;
    uint8_t data_buffer[] = {REG_ADDR_HUM};
    ReadI2C(data_buffer, &data);

    uint16_t hum = data.OutputBuffer[0] << 8 | data.OutputBuffer[1];
    float humidity = (((125.0 * hum) / 65536.0) - 6.0);

    vTaskDelay(100 / portTICK_RATE_MS);

    printf("Buffers: %d, %d\n", data.OutputBuffer[0], data.OutputBuffer[1]);

    char temp1[8];
    sprintf(temp1, "%.2f", humidity);
    // float humidity = ((tempbuffer[0] * 256.0) + tempbuffer[1]);
    // humidity = ((125 * humidity) / 65536.0) - 6;
    printf("Humidity: %.2f\n", humidity);
    *humidityValue = temp1;

    uint8_t temperatureBuffer[] = {REG_ADDR_TEMP};
    ReadI2C(temperatureBuffer, &data);

    uint16_t temp = data.OutputBuffer[0] << 8 | data.OutputBuffer[1];
    float celsTemp = ((175.72 * temp) / 65536.0) - 46.85;
    vTaskDelay(100 / portTICK_RATE_MS);
    printf("Temperature: %.2f\n", celsTemp);
    //Temperature calculator
    // myI2C.writeBit(DEVICE_ADDR, REG_ADDR_TEMP, 2, 0);
    // myI2C.readBytes(DEVICE_ADDR, REG_ADDR_TEMP, LENGTH, buffer);

    // float temp = ((buffer[0] * 256.0) + buffer[1]);
    // float celsTemp = ((175.72 * temp) / 65536.0) - 46.85;
    // printf("Temperature: %.2f\n", celsTemp);
    // //float to char array
     char temp2[8];
     sprintf(temp2, "%.2f", celsTemp);
    // //char array to string
     *temperatureValue = temp2;
    //   myI2C.close();
}