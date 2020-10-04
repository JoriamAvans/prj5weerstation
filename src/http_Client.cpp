#include "http_Client.h"
#include "esp_log.h"
static const char* TAG = "MyModule";
void http_Client::init_http(){
 //esp_http_client_init();
 /* 
 

        esp_http_client_init(): To use the HTTP client, the first thing we must do
        is create an esp_http_client by pass into this function with the 
        esp_http_client_config_t configurations. Which configuration values we do not 
        define, the library will use default.

        esp_http_client_perform(): The esp_http_client argument created from the 
        init function is needed. This function performs all operations of the 
        esp_http_client, from opening the connection, sending data, downloading 
        data and closing the connection if necessary. All related events will be 
        invoked in the event_handle (defined by esp_http_client_config_t). This 
        function performs its job and blocks the current task until it’s done

        esp_http_client_cleanup(): After completing our esp_http_client’s task, 
        this is the last function to be called. It will close the connection 
        (if any) and free up all the memory allocated to the HTTP client
 */

esp_http_client_config_t config = {
    .url = "http://httpbin.org/anything",
};

esp_http_client_handle_t client = esp_http_client_init(&config);
esp_err_t err = esp_http_client_perform(client);

if (err == ESP_OK){
    ESP_LOGI(TAG, "Status = %d, content_length = %d",
    esp_http_client_get_status_code(client),
    esp_http_client_get_content_length(client));
}
esp_http_client_cleanup(client);
}