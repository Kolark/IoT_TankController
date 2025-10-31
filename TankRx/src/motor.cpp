#include "Motor.h"
#include <Arduino.h>

void MotorControl::setupMotor(uint8_t inA, uint8_t inB, uint8_t pwm)
{
    m_inA = inA;
    m_inB = inB;

    pinMode(m_inA, OUTPUT);
    pinMode(m_inB, OUTPUT);
    setDirection(currentA, currentB);
}

void MotorControl::setDirection(uint8_t A, uint8_t B){
    currentA = A;
    currentB = B;
    digitalWrite(m_inA, currentA);
    digitalWrite(m_inB, currentB);
}