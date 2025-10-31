#include "TankController.h"
#include <Arduino.h>
#include <map>

std::map<String, TankState> stateMap = {
    {"STOP",     TankState::STOP},
    {"FORWARD",  TankState::FORWARD},
    {"BACKWARD", TankState::BACKWARD},
    {"RL",       TankState::RL},
    {"RR",       TankState::RR}
};

TankController::TankController(MotorControl& leftMotor, MotorControl& rightMotor)
: m_leftMotor(leftMotor), m_rightMotor(rightMotor)
{
}

void TankController::SetCommand(const char* cmd)
{
    TankState state = stateMap[cmd];
    currentState = state;
    switch (state)
        {
            case TankState::STOP:
                m_leftMotor.setDirection(LOW, LOW);
                m_rightMotor.setDirection(LOW, LOW);
                Serial.println("stopping");
                break;
            case TankState::FORWARD:
                Serial.println("moving f");
                m_leftMotor.setDirection(HIGH, LOW);
                m_rightMotor.setDirection(HIGH, LOW);
                break;
            case TankState::BACKWARD:
                Serial.println("moving b");
                m_leftMotor.setDirection(LOW, HIGH);
                m_rightMotor.setDirection(LOW, HIGH);
                break;
            case TankState::RL:
                Serial.println("RL");
                m_leftMotor.setDirection(HIGH, LOW);
                m_rightMotor.setDirection(LOW, HIGH);
                break;
            case TankState::RR:
                Serial.println("RR");
                m_leftMotor.setDirection(LOW, HIGH);
                m_rightMotor.setDirection(HIGH, LOW);
                break;
            default:
                m_leftMotor.setDirection(LOW, LOW);
                m_rightMotor.setDirection(LOW, LOW);
                break;
        }
}