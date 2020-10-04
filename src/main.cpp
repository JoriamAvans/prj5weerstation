/*
Documents used for programming:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#how-to-write-a-wi-fi-application

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#esp32-wi-fi-ap-general-scenario

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_client.html

http://httpbin.org/
*/

extern "C" void app_main();

#include "nvs_flash.h"
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_http_client.h"
#include "http_Client.h"
#include "espWiFiConnect.h"

#include "lwip/err.h"
#include "lwip/sys.h"
void init_NVS();

void init_esp();
void config_esp();
void connect_esp();

EventGroupHandle_t eventgroupvariable;
espWiFiConnect wificonnect;

void app_main(void)
{
  // return; //endless loop killer

  init_NVS();

  // Init Phase
  wificonnect.init_WiFi();
  // Configuration Phase
  wificonnect.config_WiFi("ESP", "Welkom@67");
  // Connection Phase
  wificonnect.conn_WiFi();

}



void init_NVS()
{
  // Initialize non-volatile storage
  esp_err_t ret = nvs_flash_init();
  if (ret == (ESP_ERR_NVS_NO_FREE_PAGES || ESP_ERR_NVS_NEW_VERSION_FOUND))
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
}
