#ifndef WEBSOCKETS
#define WEBSOCKETS

#include <ArduinoWebsockets.h>

typedef std::function<void(String)> MessageCallback;

void handleWebsocketEvent(websockets::WebsocketsEvent event, String data);
void handleWebsocketMessage(websockets::WebsocketsMessage message);

class WSManager {
public:
    bool ws_connected;
    websockets::WebsocketsClient ws_client;
    MessageCallback on_message;

    void sendMessage(const char* msg);
    void beginWebSocket(const char* host, uint16_t port, MessageCallback messageCallback);
};

extern WSManager WSM;

#endif


