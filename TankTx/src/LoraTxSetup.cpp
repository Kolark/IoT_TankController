
#include "LoraTxSetup.h"

void LORATX::setupLora(){
    
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


void LORATX::sendLoraPacket(char* msg){
    Serial.println("Sending packet: ");
    Serial.println(msg);
    LoRa.beginPacket();
    LoRa.print(msg);
    // if(v == 0){
    //     LoRa.print( "{\"COMMAND\": 0, \"pwma\": 200}");
    // }
    // else if(v == 1){
    //     LoRa.print( "{\"COMMAND\": 1, \"pwma\": 200}");
    // }
    // else if(v == 2){
    //     LoRa.print( "{\"COMMAND\": 2, \"pwma\": 200}");
    // }
    // else if(v == 3){
    //     LoRa.print( "{\"COMMAND\": 3, \"pwma\": 200}");
    // }
    // else if(v == 4){
    //     LoRa.print( "{\"COMMAND\": 4, \"pwma\": 200}");
    // }
    LoRa.endPacket();
    delay(500);
}