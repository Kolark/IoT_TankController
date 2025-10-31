// Only supports SX1276/SX1278

#include <ESP8266WiFi.h>
#include "ws.h"

const char* ssid = "GUAYACAN";
const char* password = "Guayacan25";
const char* websockets_server_host = "ec2-34-229-102-184.compute-1.amazonaws.com";
const uint16_t websockets_server_port = 5001;

void onMessageReceived(String msg){
    Serial.println(msg);
}

void setup()
{
  Serial.begin(115200);

  delay(100);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

 Serial.println("");
 Serial.println("WiFi connected");

  delay(100);
  WSM.beginWebSocket(websockets_server_host, websockets_server_port, onMessageReceived);

  delay(100);

    // LORATX::setupLora();
}

void loop()
{
    WSM.ws_client.poll();
    delay(5);
}