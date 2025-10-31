// Only supports SX1276/SX1278

#include "LoraTXSetup.h"
#include "WifiSetup.h"
#include "ws.h"
#include <ArduinoJson.h>
const char* ssid = "UPBWiFi";
const char* password = "";
const char* websockets_server_host = "ec2-34-239-143-41.compute-1.amazonaws.com";
const uint16_t websockets_server_port = 5001;

void onMessageReceived(String msg){
    Serial.println(msg);

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, msg);
    
    if (!error) {
        String msgType = doc["type"];
        String dataObject = doc["data"]; 
        // String outputString;
        // serializeJson(dataObject, outputString);

        Serial.printf("[WS] <<< %s\n", dataObject.c_str());
        LORATX::sendLoraPacket(dataObject.c_str());
    }
}

void setup()
{
    Serial.begin(115200);
    wifi_setup::connectWiFi(ssid, password);
    WSM.beginWebSocket(websockets_server_host, websockets_server_port, onMessageReceived);

    delay(100);

    LORATX::setupLora();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[WiFi] Lost connection, attempting reconnect...");
        WSM.ws_connected = false;
        if (WSM.ws_client.available()) {
            WSM.ws_client.close();
        }
        wifi_setup::connectWiFi(ssid, password);
        WSM.beginWebSocket(websockets_server_host, websockets_server_port, onMessageReceived);
        delay(500);
        return;
    }

    WSM.ws_client.poll();
    delay(5);
}