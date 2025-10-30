#ifndef WEBSOCKETS
#define WEBSOCKETS

#include <ArduinoWebsockets.h>

// using namespace websockets;

namespace WS {
typedef std::function<void(String)> MessageCallback;

MessageCallback onMessage = nullptr;

websockets::WebsocketsClient wsClient;
bool wsConnected = false;

void handleWebsocketEvent(websockets::WebsocketsEvent event, String data);
void handleWebsocketMessage(websockets::WebsocketsMessage message);
void sendMessage(const char* msg);
void beginWebSocket(const char* host, uint16_t port, WS::MessageCallback messageCallback);
}
#endif


