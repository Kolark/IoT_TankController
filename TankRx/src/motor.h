#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>

class MotorControl
{
public:
  void setupMotor(uint8_t inA, uint8_t inB, uint8_t pwm);
  void setDirection(uint8_t A, uint8_t B);

private:
  uint8_t m_inA, m_inB, m_pwm;
  uint8_t currentA, currentB;
  uint16_t currentPwm;
};

#endif