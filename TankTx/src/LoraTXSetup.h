#ifndef LORATX_SETUP
#define LORATX_SETUP

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

namespace LORATX {
    void setupLora();
    void sendLoraPacket(char* msg);
}

#endif