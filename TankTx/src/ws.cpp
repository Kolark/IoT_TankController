#include "ws.h"
#include <ArduinoJson.h>
void WS::handleWebsocketEvent(websockets::WebsocketsEvent event, String data) {
    switch (event) {
        case websockets::WebsocketsEvent::ConnectionOpened:
            Serial.println("[WS] Event: connection opened");
            WS::wsConnected = true;
            break;
        case websockets::WebsocketsEvent::ConnectionClosed:
            Serial.println("[WS] Event: connection closed");
            WS::wsConnected = false;
            break;
        case websockets::WebsocketsEvent::GotPing:
            Serial.println("[WS] Event: ping");
            break;
        case websockets::WebsocketsEvent::GotPong:
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

void WS::handleWebsocketMessage(websockets::WebsocketsMessage message) {
    if (message.isText()) {
        const String &payload = message.data();
        Serial.printf("[WS] <<< %s\n", payload.c_str());
        if (WS::onMessage) { WS::onMessage(payload); }
    }
}

void WS::sendMessage(const char* msg) {
    if (WS::wsConnected) {
        JsonDocument doc;
        doc["type"] = "message";
        doc["data"] = msg;

        String payload;
        serializeJson(doc, payload);

        WS::wsClient.send(payload);
        Serial.printf("[WS] >>> %s\n", payload.c_str());
    }
}

void WS::beginWebSocket(const char* host, uint16_t port, WS::MessageCallback messageCallback) {
    if (WS::wsClient.available()) {
        WS::wsClient.close();
    }

    String uri = String("ws://") + host + ":" + port;
    Serial.printf("[WS] Connecting to %s\n", uri.c_str());

    WS::wsClient.onEvent(WS::handleWebsocketEvent);
    WS::wsClient.onMessage(WS::handleWebsocketMessage);
    WS::onMessage = messageCallback;
    if (!WS::wsClient.connect(uri)) {
        Serial.println("[WS] Connection attempt failed");
        WS::wsConnected = false;
        return;
    }
}