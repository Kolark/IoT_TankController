#ifndef WIFI_SETUP
#define WIFI_SETUP
#include <WiFi.h>
namespace wifi_setup {
    void connectWiFi(const char* ssid, const char* password);
}

#endif