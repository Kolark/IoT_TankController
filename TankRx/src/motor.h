#ifndef MOTOR_CONTROL  // <-- 1. Start of Header Guard
#define MOTOR_CONTROL
#include <stdint.h>
namespace Motor {
  class MotorControl
  {
  public:
    void setupMotor(uint8_t inA, uint8_t inB, uint8_t pwm);
    void setDirection(uint8_t A, uint8_t B);
    // void setSpeed(uint8_t s);
    // void update(float dt);

  private:
    uint8_t m_inA, m_inB, m_pwm;
    uint8_t currentA, currentB;
    uint16_t currentPwm;
    // uint8_t targetPwm;
    // uint8_t rampSpeed = 15;
    // bool rampPwm;
  };

}
#endif