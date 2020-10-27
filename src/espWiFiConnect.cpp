#include "espWiFiConnect.h"

static void Event_Handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
int positief_signaal = 0;
int connection_status = 1;
int connection_watchdog = 0;
const char *Wifi_ssid;
const char *Wifi_pw;

bool espWiFiConnect::conn_WiFi()
{
    esp_wifi_start();

    while (positief_signaal != 1)
    {
        //Buffer om synchronisatie toe te laten.
        if (connection_watchdog >= 100) {
            printf("Connection watchdog triggered, aborting..\n");
            return false;
        }
        if (connection_status == 0) {
            printf("Connection failed.\n");
            return false;
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
    esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &Event_Handler);
    esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &Event_Handler);
    printf("Event handler unregistered succesfully.\n");
    return true;
}

bool espWiFiConnect::config_WiFi(const char *ssid, const char *pw)
{
    Wifi_ssid = ssid;
    Wifi_pw = pw;

    init_WiFi();
    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t configSTA = {};

    strcpy((char *)configSTA.sta.ssid, ssid);   //SSID instellen.
    strcpy((char *)configSTA.sta.password, pw); //Wachtwoord instellen.

    //Geprogrammeerd volgens de instructies: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html#how-to-write-a-wi-fi-application

    configSTA.sta.scan_method = WIFI_FAST_SCAN;
    configSTA.sta.bssid_set = 0;
    configSTA.sta.channel = 0;
    esp_wifi_set_config(WIFI_IF_STA, &configSTA);
    return conn_WiFi();
}

void espWiFiConnect::init_WiFi()
{
    esp_netif_init();
    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&config);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &Event_Handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &Event_Handler, NULL);
}

static void Event_Handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    printf("Event handler called\n");

    if (WIFI_EVENT == event_base)
    {
        if (event_id == WIFI_EVENT_STA_START)
        {
            esp_wifi_connect();
        }
        else if (event_id != WIFI_EVENT_STA_CONNECTED)
        {
            esp_wifi_disconnect();
            esp_wifi_stop();
            esp_wifi_deinit();
            esp_netif_deinit();
            connection_status = 0;
            return;
        }
    }

    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        positief_signaal = 1;
    }
}