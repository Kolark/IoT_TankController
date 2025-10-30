// Only supports SX1276/SX1278
#include <LoRa.h>
#include "LoRaBoards.h"

#ifndef CONFIG_RADIO_FREQ
#define CONFIG_RADIO_FREQ           920.0
#endif
#ifndef CONFIG_RADIO_OUTPUT_POWER
#define CONFIG_RADIO_OUTPUT_POWER   17
#endif
#ifndef CONFIG_RADIO_BW
#define CONFIG_RADIO_BW             125.0
#endif

#if !defined(USING_SX1276) && !defined(USING_SX1278)
#error "LoRa example is only allowed to run SX1276/78. For other RF models, please run examples/RadioLibExamples"
#endif

#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>

using namespace websockets;

WebsocketsClient wsClient;
bool wsConnected = false;
const char* ssid = "UPBWiFi";
const char* password = "";
const char* websockets_server_host = "ec2-98-91-209-237.compute-1.amazonaws.com";
const uint16_t websockets_server_port = 5001;

void sendLoraPacket(int v){
    Serial.println("Sending packet: ");
    Serial.println(v);
    LoRa.beginPacket();
    if(v == 0){
        LoRa.print( "{\"COMMAND\": 0, \"pwma\": 200}");
    }
    else if(v == 1){
        LoRa.print( "{\"COMMAND\": 1, \"pwma\": 200}");
    }
    else if(v == 2){
        LoRa.print( "{\"COMMAND\": 2, \"pwma\": 200}");
    }
    else if(v == 3){
        LoRa.print( "{\"COMMAND\": 3, \"pwma\": 200}");
    }
    else if(v == 4){
        LoRa.print( "{\"COMMAND\": 4, \"pwma\": 200}");
    }
    LoRa.endPacket();
    delay(500);
}

void connectWiFi() {
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

void handleWebsocketEvent(WebsocketsEvent event, String data) {
    switch (event) {
        case WebsocketsEvent::ConnectionOpened:
            Serial.println("[WS] Event: connection opened");
            wsConnected = true;
            break;
        case WebsocketsEvent::ConnectionClosed:
            Serial.println("[WS] Event: connection closed");
            wsConnected = false;
            break;
        case WebsocketsEvent::GotPing:
            Serial.println("[WS] Event: ping");
            break;
        case WebsocketsEvent::GotPong:
            Serial.println("[WS] Event: pong");
            break;
        default:
            if (data.length() > 0) {
                Serial.printf("[WS] Event %d data: %s\n",
                              static_cast<int>(event), data.c_str());
            }
            break;
    }
}

void handleWebsocketMessage(WebsocketsMessage message) {
    if (message.isText()) {
        const String &payload = message.data();
        Serial.printf("[WS] <<< %s\n", payload.c_str());
        
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);
        
        if (!error) {
            String msgType = doc["type"];
            String msgData = doc["data"];
            
            if (msgType == "notification") {
                Serial.printf("[NOTIFICATION] %s\n", msgData.c_str());
                if(msgData == "STOP"){
                    sendLoraPacket(0);
                }
                else if (msgData=="FORWARD"){
                    sendLoraPacket(1);
                }
                else if (msgData=="BACKWARD"){
                    sendLoraPacket(2);
                }
                else if (msgData=="RL"){
                    sendLoraPacket(3);
                }
                else if (msgData=="RR"){
                    sendLoraPacket(4);
                }
            } else if (msgType == "response") {
                Serial.printf("[RESPONSE] %s\n", msgData.c_str());
            }
        }
    }
}

void sendMessage(const char* msg) {
    if (wsConnected) {
        DynamicJsonDocument doc(1024);
        doc["type"] = "message";
        doc["data"] = msg;
        
        String payload;
        serializeJson(doc, payload);
        
        wsClient.send(payload);
        Serial.printf("[WS] >>> %s\n", payload.c_str());
    }
}

void beginWebSocket() {
    if (wsClient.available()) {
        wsClient.close();
    }

    String uri = String("ws://") + websockets_server_host + ":" + websockets_server_port;
    Serial.printf("[WS] Connecting to %s\n", uri.c_str());

    wsClient.onEvent(handleWebsocketEvent);
    wsClient.onMessage(handleWebsocketMessage);

    if (!wsClient.connect(uri)) {
        Serial.println("[WS] Connection attempt failed");
        wsConnected = false;
        return;
    }
}

void setupLora(){
    setupBoards();
    // When the power is turned on, a delay is required.
    delay(1500);

#ifdef  RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    Serial.println("LoRa Sender");
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(CONFIG_RADIO_FREQ * 1000000)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    LoRa.setTxPower(CONFIG_RADIO_OUTPUT_POWER);

    LoRa.setSignalBandwidth(CONFIG_RADIO_BW * 1000);

    LoRa.setSpreadingFactor(10);

    LoRa.setPreambleLength(16);

    LoRa.setSyncWord(0xAB);

    LoRa.disableCrc();

    LoRa.disableInvertIQ();

    LoRa.setCodingRate4(7);
}



void setup()
{
    Serial.begin(115200);
    connectWiFi();
    beginWebSocket();

    delay(100);

    setupLora();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[WiFi] Lost connection, attempting reconnect...");
        wsConnected = false;
        if (wsClient.available()) {
            wsClient.close();
        }
        connectWiFi();
        beginWebSocket();
        delay(500);
        return;
    }

    wsClient.poll();
    
    static unsigned long lastSend = 0;
    if (wsConnected && millis() - lastSend > 10000) {
        sendMessage("Hello from LilyGO");
        lastSend = millis();
    }
    
    delay(5);
}