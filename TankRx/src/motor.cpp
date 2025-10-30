#include "motor.h"
#include <Arduino.h>

void Motor::MotorControl::setupMotor(uint8_t inA, uint8_t inB, uint8_t pwm)
{
    m_inA = inA;
    m_inB = inB;
    // m_pwm = pwm;

    pinMode(m_inA, OUTPUT);
    pinMode(m_inB, OUTPUT);
    // pinMode(m_pwm, OUTPUT);

    // currentPwm = 255;
    setDirection(currentA, currentB);
    // setSpeed(currentPwm);
}

void Motor::MotorControl::setDirection(uint8_t A, uint8_t B){
    currentA = A;
    currentB = B;
    digitalWrite(m_inA, currentA);
    digitalWrite(m_inB, currentB);
}

// void Motor::MotorControl::setSpeed(uint8_t s){
//     // targetPwm = s;
//     // currentPwm = s;
//     analogWrite(m_pwm, currentPwm);
// }

// void Motor::MotorControl::update(float dt){
//     if(rampPwm){
//         currentPwm += static_cast<uint16_t>(rampSpeed * dt);
//         if(currentPwm > targetPwm)
//         {
//             currentPwm = targetPwm;
//             rampPwm = false;
//         }
//         analogWrite(m_pwm, currentPwm);
//     }
// }
