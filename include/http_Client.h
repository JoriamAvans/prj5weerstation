#pragma once

#include "esp_http_client.h"
class http_Client{
public:

    /**
     * @brief Deze functie is voor het regelen van de http initialisatie
     * 
     * @param urlArg De url waar mee verbonden dient te worden.
     */
    void init_http(char* urlArg);
    
};