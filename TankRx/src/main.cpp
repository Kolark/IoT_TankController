#include <Arduino.h>
#include "LORA/LilyGoSetup.h"
#include <ArduinoJson.h>
#include <motor.h>

constexpr uint8_t LEFT_IN1  = 22;
constexpr uint8_t LEFT_IN2  = 21;
constexpr uint8_t LEFT_PWM  = 25;
constexpr uint8_t RIGHT_IN1 = 15;
constexpr uint8_t RIGHT_IN2 = 13;
constexpr uint8_t RIGHT_PWM = 14;

Motor::MotorControl mc1;
Motor::MotorControl mc2;


#ifndef CONFIG_RADIO_FREQ
#define CONFIG_RADIO_FREQ           920.0
#endif
#ifndef CONFIG_RADIO_OUTPUT_POWER
#define CONFIG_RADIO_OUTPUT_POWER   17
#endif
#ifndef CONFIG_RADIO_BW
#define CONFIG_RADIO_BW             125.0
#endif

unsigned long previousTime = 0;
float deltaTime = 0;
int currentCMD = 0;
void setup()
{
    Serial.begin(115200);
    LoraConfig::SetupLORA(CONFIG_RADIO_FREQ, CONFIG_RADIO_OUTPUT_POWER, CONFIG_RADIO_BW);
    delay(1000);
    mc1.setupMotor(LEFT_IN1,  LEFT_IN2,  LEFT_PWM);
    mc2.setupMotor(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM);
    previousTime = millis();
}

void dt(){
    unsigned long currentTime = millis();
    unsigned long dt_ms = currentTime - previousTime;
    deltaTime = (float)dt_ms / 1000.0;
}

void loop()
{
    // mc1.setDirection(HIGH, LOW);
    // mc2.setDirection(HIGH, LOW);
    // delay(2000);

    // mc1.setDirection(LOW, LOW);
    // mc2.setDirection(LOW, LOW);
    // delay(2000);

    // mc1.setDirection(LOW, HIGH);
    // mc2.setDirection(LOW, HIGH);

    // delay(2000);

    // mc1.setDirection(LOW, LOW);
    // mc2.setDirection(LOW, LOW);
    // delay(2000);

//   3. Convert dt to seconds (optional, but often useful)
    String resp = LoraConfig::ReceivePacket();
    if(!resp.isEmpty()){
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, resp.c_str());

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(resp.c_str());
            Serial.println(error.f_str());
            return;
        }
            // Access values
        int cmd  = doc["COMMAND"];
        Serial.println("COMMAND");
        Serial.println(resp.c_str());
        Serial.println(cmd);
        mc1.setDirection(LOW, LOW);
        mc2.setDirection(LOW, LOW);
        delay(300);

        switch (cmd)
        {
            case 0:
                mc1.setDirection(LOW, LOW);
                mc2.setDirection(LOW, LOW);
                Serial.println("stopping");
                break;
            case 1:
                Serial.println("moving f");
                mc1.setDirection(HIGH, LOW);
                mc2.setDirection(HIGH, LOW);
                break;
            case 2:
                Serial.println("moving b");
                mc1.setDirection(LOW, HIGH);
                mc2.setDirection(LOW, HIGH);
                break;
            case 3:
                Serial.println("RL");
                mc1.setDirection(HIGH, LOW);
                mc2.setDirection(LOW, HIGH);
                break;
            case 4:
                Serial.println("RR");
                mc1.setDirection(LOW, HIGH);
                mc2.setDirection(HIGH, LOW);
                break;
            default:
                mc1.setDirection(LOW, LOW);
                mc2.setDirection(LOW, LOW);
                break;
        }
        currentCMD = cmd;
        // int leverB  = doc["leverB"];
    }
}