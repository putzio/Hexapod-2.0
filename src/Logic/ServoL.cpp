#include "Logic/ServoL.hpp"
// #include "pico/double.h"

static inline uint16_t map(float x, uint16_t sMin, uint16_t sMax, uint16_t dMin, uint16_t dMax)
{
    return ((x - (float)sMin) * (dMax - dMin) / (sMax - sMin) + dMin);
}

uint16_t ServoL::CalculateLeft(uint16_t pos)
{
    int pos90 = MapPositionToMs(90);
    // get the distance from 90 degrees
    int distance = pos90 - pos;
    // return another direction
    return pos90 + distance;
}
void ServoL::SetPwm(uint16_t value)
{
    pwmValue = value;
}

uint16_t ServoL::MapPositionToMs(uint8_t position)
{
    return map(position, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS);
}

uint16_t ServoL::MapMsToPosition(uint16_t msPosition)
{
    return map(position, SERVO_MIN_MS, SERVO_MAX_MS, 0, 180);
}

void ServoL::WriteMs()
{
    if (servoSide == leftServo)
        SetPwm(CalculateLeft(currentPosition));
    else
        // Set channel output high for one cycle before dropping
        SetPwm(currentPosition);
}

ServoL::ServoL(ServoSide side):ServoVelocity()
{
    currentPosition = (SERVO_MIN_MS + SERVO_MAX_MS) / 2;
    msPosition = currentPosition;
    done = true;
    servoSide = side;
}

void ServoL::GoToPosition()
{
    CalculateVelocity(currentPosition - msPosition);
    if (!done)
    {
        // this->currentPosition+=((this->currentPosition-this->msPosition)/300);
        if (currentPosition > msPosition)
            currentPosition -= GetVelocity();
        else
            currentPosition += GetVelocity();

        // if(currentPosition - msPosition < velocity &&
        //    currentPosition - msPosition > -velocity)
        if (IS_BETWEEN(currentPosition - msPosition, -GetVelocity(), GetVelocity()))
            currentPosition = msPosition;

        // Move servo
        WriteMs();

        // If the servo has reached the final position move is done
        if (currentPosition == msPosition)
            done = true;
    }
}

// void ServoL::ChangeVelocityLimits(int v)
// {
//     minVelocity = v;
//     maxVelocity = 3 * v + 5;
// }
// void ServoL::CalculateVelocity()
// {
//     // if(currentPosition - msPosition < DISTANCE_DECCELERATION &&
//     //     currentPosition - msPosition > - DISTANCE_DECCELERATION )
//     if (IS_BETWEEN(currentPosition - msPosition, -DISTANCE_DECCELERATION, DISTANCE_DECCELERATION))
//     {
//         // deccelerate
//         velocity -= DECCELERATION;
//     }
//     else
//     {
//         // accelerate
//         velocity += ACCELERATION;
//     }

//     if (velocity < minVelocity)
//         velocity = minVelocity;
//     if (velocity > maxVelocity)
//         velocity = maxVelocity;
// }
void ServoL::ChangePosition(uint8_t pos)
{
    msPosition = MapPositionToMs(pos);
    position = pos;
    done = false;
}
void ServoL::Write(uint8_t newPosition)
{
    if (newPosition <= 180 && newPosition >= 0)
    {
        this->position = newPosition;
        this->msPosition = MapPositionToMs(position);
        currentPosition = msPosition;
        WriteMs();
    }
}

uint16_t ServoL::GetPwmValue()
{
    return pwmValue;
}

uint16_t ServoL::GetMsPosition()
{
    return msPosition;
}



