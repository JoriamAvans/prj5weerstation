#include "espWiFiConnect.h"

static void Event_Handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
int positief_signaal = 0;

void espWiFiConnect::conn_WiFi()
{
  esp_wifi_start();
  while (positief_signaal != 1)
  {
    //bezig houden met iets
  }
  //dan pas wat doen
  esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &Event_Handler);
  esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &Event_Handler);
  printf("\n\n\nJe zooi is opgeruimd a mattie\n\n\n");
}

void espWiFiConnect::config_WiFi(const char* ssid, const char* pw)
{
  esp_wifi_set_mode(WIFI_MODE_STA);
  //wifi_interface_t interfaceSTA = WIFI_IF_STA;
  wifi_config_t configSTA = {};
  strcpy((char *)configSTA.sta.ssid, ssid);
  strcpy((char *)configSTA.sta.password, pw);
  configSTA.sta.scan_method = WIFI_FAST_SCAN;
  configSTA.sta.bssid_set = 0;
  configSTA.sta.channel = 0;
  esp_wifi_set_config(WIFI_IF_STA, &configSTA);
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
  //check iets met ip event
  if (WIFI_EVENT == event_base)
  {
    //pak kaas
    if (event_id == WIFI_EVENT_STA_START)
    {
      esp_wifi_connect();
    } //vanaf hier mag ik errors handlen
    else if(event_id != WIFI_EVENT_STA_CONNECTED)
    {
      printf("Deze shit gaat helemaal fout a neef\n");
    }
  printf("HUUTSSSSS: %d\n", event_id);  //tot hier
  }

  if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
  {
    positief_signaal = 1;
    printf("\n\n\nJE HEBT VERBINDING GAPPIE\n\n\n");
  }
}