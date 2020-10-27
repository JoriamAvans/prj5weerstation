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
    /**
  * @brief Deze functie initialiseerd de connectie en verbind met de event handler
  * 
  * @note heeft geen parameters, moet alleen aangeroepen worden voor config_WiFi
  * 
  * 
  */
    void init_WiFi();
    /**
 * @brief      Deze functie is om de wifi ssid in te stellen samen met het wachtwoord
 * 
 * @note       Invullen als string: config_WiFi("JouwString", "JouwString")
 *
 * @param      ssid  De naam van de router
 * @param      pw Het wachtwoord van de router
 * @return
 *  - ESP_OK on successful
 *  - ESP_FAIL on error
 */
    bool config_WiFi(const char *ssid, const char *pw);

    /**
   * @brief Deze functie start de wifi en wacht tot de connectie weer synchroon loopt met het proces
   *        , daarna verwijderd hij de registraties van de initialisatie en print hij een bevestiging.
   * 
   * 
   */
    bool conn_WiFi();
};