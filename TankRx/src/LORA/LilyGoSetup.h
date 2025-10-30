#ifndef LORA_CONFIG
#define LORA_CONFIG

#include <LoRa.h>
#include "LoRaBoards.h"

#if !defined(USING_SX1276) && !defined(USING_SX1278)
#error "LoRa example is only allowed to run SX1276/78. For other RF models, please run examples/RadioLibExamples
#endif

namespace LoraConfig {
    void SetupLORA(double RF, double ROP, double RBW);
    String ReceivePacket();
}
#endif