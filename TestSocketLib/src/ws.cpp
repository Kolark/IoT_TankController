#include "ws.h"
#include <ArduinoJson.h>

WSManager WSM;

void handleWebsocketEvent(websockets::WebsocketsEvent event, String data) {
    switch (event) {
        case websockets::WebsocketsEvent::ConnectionOpened:
            Serial.println("[WS] Event: connection opened");
            WSM.ws_connected = true;
            break;
        case websockets::WebsocketsEvent::ConnectionClosed:
            Serial.println("[WS] Event: connection closed");
            WSM.ws_connected = false;
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

void handleWebsocketMessage(websockets::WebsocketsMessage message) {
    if (message.isText()) {
        const String &payload = message.data();
        Serial.printf("[WS] <<< %s\n", payload.c_str());
        if (WSM.on_message) { WSM.on_message(payload); }
    }
}

void WSManager::sendMessage(const char* msg) {
    if (WSM.ws_connected) {
        JsonDocument doc;
        doc["type"] = "message";
        doc["data"] = msg;

        String payload;
        serializeJson(doc, payload);

        WSM.ws_client.send(payload);
        Serial.printf("[WS] >>> %s\n", payload.c_str());
    }
}

void WSManager::beginWebSocket(const char* host, uint16_t port, MessageCallback messageCallback) {
    if (WSM.ws_client.available()) {
        WSM.ws_client.close();
    }

    String uri = String("ws://") + host + ":" + port;
    Serial.printf("[WS] Connecting to %s\n", uri.c_str());

    ws_client.onEvent(handleWebsocketEvent);
    ws_client.onMessage(handleWebsocketMessage);
    WSM.on_message = messageCallback;
    if (!ws_client.connect(uri)) {
        Serial.println("[WS] Connection attempt failed");
        WSM.ws_connected = false;
        return;
    }
}