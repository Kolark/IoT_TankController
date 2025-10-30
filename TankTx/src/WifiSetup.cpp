#include "WifiSetup.h"

void wifi_setup::connectWiFi(const char* ssid,const char* password) {
    Serial.printf("[WiFi] Connecting to %s\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    const uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 30000) {
        Serial.print('.');
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.printf("[WiFi] Connected. IP=%s RSSI=%d dBm\n",
                      WiFi.localIP().toString().c_str(), WiFi.RSSI());
        return;
    }

    Serial.println("\n[WiFi] Failed to connect. Restarting...");
    delay(3000);
    ESP.restart();
}