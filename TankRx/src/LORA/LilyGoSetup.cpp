#include "LilyGoSetup.h"

void LoraConfig::SetupLORA(double RF, double ROP, double RBW){
    setupBoards();
    // When the power is turned on, a delay is required.
    delay(1500);

    Serial.println("LoRa Receiver");

#ifdef  RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(RF * 1000000)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    LoRa.setTxPower(ROP);

    LoRa.setSignalBandwidth(RBW * 1000);

    LoRa.setSpreadingFactor(10);

    LoRa.setPreambleLength(16);

    LoRa.setSyncWord(0xAB);

    LoRa.disableCrc();

    LoRa.disableInvertIQ();

    LoRa.setCodingRate4(7);

    // put the radio into receive mode
    LoRa.receive();
}

String LoraConfig::ReceivePacket(){
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {

        String recv = "";
        // read packet
        while (LoRa.available()) {
            recv += (char)LoRa.read();
        }
        return recv;
    }
    return emptyString;
}