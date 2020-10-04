#pragma once

#include "nvs_flash.h"
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"

#include "lwip/err.h"
#include "lwip/sys.h"

class espWiFiConnect
{
public:
 
  void init_WiFi();
  void config_WiFi(const char* ssid, const char* pw);
  void conn_WiFi();
  
};