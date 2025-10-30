// Only supports SX1276/SX1278

#include "LoraTXSetup.h"
#include "WifiSetup.h"
#include "ws.h"

const char* ssid = "UPBWiFi";
const char* password = "";
const char* websockets_server_host = "ec2-98-91-209-237.compute-1.amazonaws.com";
const uint16_t websockets_server_port = 5001;

// void onMessageReceived(String msg){
//     Serial.println(msg);
// }

void setup()
{
    // Serial.begin(115200);
    // wifi_setup::connectWiFi(ssid, password);
    // WS::beginWebSocket(websockets_server_host, websockets_server_port, onMessageReceived);

    // delay(100);

    // LORATX::setupLora();
}

void loop()
{
    // if (WiFi.status() != WL_CONNECTED) {
    //     Serial.println("[WiFi] Lost connection, attempting reconnect...");
    //     WS::wsConnected = false;
    //     if (WS::wsClient.available()) {
    //         WS::wsClient.close();
    //     }
    //     wifi_setup::connectWiFi(ssid, password);
    //     WS::beginWebSocket(websockets_server_host, websockets_server_port, onMessageReceived);
    //     delay(500);
    //     return;
    // }

    // WS::wsClient.poll();

    // static unsigned long lastSend = 0;
    // if (WS::wsConnected && millis() - lastSend > 10000) {
    //     WS::sendMessage("Hello from LilyGO");
    //     lastSend = millis();
    // }

    // delay(5);
}