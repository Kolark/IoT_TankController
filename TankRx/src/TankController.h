#ifndef TANK_CONTROL_H
#define TANK_CONTROL_H
#include "Motor.h"

enum class TankState
{
    STOP = 0,
    FORWARD = 1,
    BACKWARD = 2,
    RL = 3,
    RR = 4
};

class TankController
{
    public:
        TankController(MotorControl& leftMotor, MotorControl& rightMotor);
        void SetCommand(const char* cmd);
        TankState currentState = TankState::STOP;

    private:
        MotorControl& m_leftMotor;
        MotorControl& m_rightMotor;
};

#endif