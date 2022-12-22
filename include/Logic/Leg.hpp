#pragma once

#include "Logic/ServoL.hpp"
#include "enum_types.h"
#include "Logic/SlaveServo.hpp"

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
    private:    
    ServoL master;
    SlaveServo slave;
    int16_t velocityLimits[2] = {MIN_VELOCITY, MAX_VELOCITY};//struct???
    int16_t legXVelocity = 10;//mm/s

    public:
    enum LegPosition
    {
        kBack,
        kBackDown,
        kBackUp,
        kForward,
        kForwardDown,
        kForwardUp
    };
    static const uint16_t legLength = 700;//mm
    int maxPos = MASTER_SERVO_MAX_POS;
    int minPos = MASTER_SERVO_MIN_POS;
    int upPos = SLAVE_UP_POSITION;

public:

    Leg(ServoL::ServoSide side = ServoL::rightServo, SlaveServo::ServoPosition sBack = SlaveServo::slaveBack);
    void InitLeg();
    void ChangeLegVelocityLimits(int vMin, int vMax);
    const int16_t* GetVelocityLimits();


    
    // void ChangeHight(uint16_t hight);
    // void LegPeriodicProcess()
    // {

    // }



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
    // void DisableLeg();
};