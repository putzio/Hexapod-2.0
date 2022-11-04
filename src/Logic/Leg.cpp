#include "Logic/Leg.hpp"


Leg::Leg(ServoL::ServoSide side, SlaveServo::ServoPosition sBack)
{
    master = ServoL(side);
        slave = SlaveServo(side, sBack);
        if (!sBack)
        {
            maxPos = 180 - MASTER_SERVO_MIN_POS;
            minPos = 180 - MASTER_SERVO_MAX_POS;
            upPos = 180 - SLAVE_UP_POSITION;
        }
}

void Leg::InitLeg(){
    // master.Enable();
    // master.Write(90);
    // slave.enableSlave = true;
    // slave.Enable();
    // slave.SlavePosition(master.position);
}

void Leg::ChangeLegVelocityLimits(int vMin, int vMax)
{
    master.ChangeVelocityLimits(vMin, vMax);
    slave.ChangeVelocityLimits(vMin, vMax);
}

void Leg::WriteMaster(int position, bool slaveEnabled)
{
    master.Write(position);
    if (slaveEnabled)
    {
        slave.enableSlave = true;
        slave.UpdateSlavePosition(position);
    }
    else
    {
        slave.enableSlave = false;
    }
}
// Changes the desired position of the master
void Leg::ChangePosition(uint8_t pos, bool slaveEnabled)
{
    master.ChangePosition(pos);
    slave.enableSlave = slaveEnabled;
}

void Leg::GoToPositionMaster()
{
    master.GoToPosition();
    slave.UpdateSlavePosition(master.MapMsToPosition(master.position));//map(master.currentPosition, SERVO_MIN_MS, SERVO_MAX_MS, 0.0, 180.0));
}
// Changes only Slave desired position
void Leg::ChangePositionSlave(uint8_t pos)
{
    slave.ChangePosition(pos);
}
// Both servos are getting closer to the position set in ChangePosition()
void Leg::GoToPosition()
{
    if (!master.done)
        master.GoToPosition();
    if (!slave.done)
        slave.GoToPosition();
}

// automatically change position depending on the State, enableSlave and Leg properties (minPos, maxPos, upPos)
void Leg::ChooseMove(State s, bool enableSlave)
{
    switch (s)
    {
    case Forward:
    {
        ChangePosition(maxPos, enableSlave);
        break;
    }
    case Down:
    {
        // ChangePositionSlave(slave.CalculatePosition(master.position));
        slave.UpdateSlavePosition(master.position);
        break;
    }
    case Back:
    {
        ChangePosition(minPos, enableSlave);
        break;
    }
    case Up:
    {
        ChangePositionSlave(upPos);
        break;
    }
    default:
    {
        //It should not get here
        break;
    }
    }
}
bool Leg::Move()
{
    if (!master.done)
    {
        GoToPositionMaster();
        return false;
    }
    else if (!slave.done)
    {
        GoToPosition();
        return false;
    }
    else
        return true;
}
bool Leg::MoveDone()
{
    if (master.done && slave.done)
        return true;
    else
        return false;
}
// void Leg::DisableLeg()
// {
//     master.Disable();
//     slave.Disable();
// }