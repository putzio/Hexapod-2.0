#pragma once
#include "Servo.hpp"
#include "enum_types.h"
// SERVO POSITIONS
#define MASTER_SERVO_MIN_POS 100
#define MASTER_SERVO_MAX_POS 130
#define SLAVE_UP_POSITION 5

/*
    Servos arrangement in the leg:
    |___O__ <-- Master Servo
       /
      /
     O      <-- Slave Servo
      \
       \
*/
class Leg
{
public:
    Servo master;
    SlaveServo slave;
    int maxPos = MASTER_SERVO_MAX_POS;
    int minPos = MASTER_SERVO_MIN_POS;
    int upPos = SLAVE_UP_POSITION;

    void InitLeg();

public:
    Leg(int pinMaster = 2, int pinSlave = 3, bool leftLeg = false, bool sBack = true, int16_t calibrationMaster = 0, int16_t calibrationSlave = 0);
    void ChangeLegVelocityLimits(int v);
    // Writes master position and if the slave is enabled slave adjusts its angle,
    // so the height of the leg does not change
    void WriteMaster(int position, bool slaveEnabled);
    // Changes the desired position of the master
    void ChangePosition(uint8_t pos, bool slaveEnabled);

    void GoToPositionMaster();
    // Changes only Slave desired position
    void ChangePositionSlave(uint8_t pos);
    // Both servos are getting closer to the position set in ChangePosition()
    void GoToPosition();

    // automatically change position depending on the State, enableSlave and Leg properties (minPos, maxPos, upPos)
    void ChooseMove(State s, bool enableSlave);
    bool Move();
    bool MoveDone();
    void DisableLeg();
};