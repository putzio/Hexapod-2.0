#include "Logic/ServoL.hpp"
#include "pico/double.h"

uint16_t map(float x, uint16_t sMin, uint16_t sMax, uint16_t dMin, uint16_t dMax)
{
    return ((x - (float)sMin) * (dMax - dMin) / (sMax - sMin) + dMin);
}

uint16_t ServoL::CalculateLeft(uint16_t pos)
{
    int pos90 = map(90, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS);
    // get the distance from 90 degrees
    int distance = pos90 - pos;
    // return another direction
    return pos90 + distance;
}
void ServoL::SetPwm(uint16_t value)
{
    pwmValue = value;
}

void ServoL::WriteMs()
{
    if (left)
        SetPwm(CalculateLeft(currentPosition));
    else
        // Set channel output high for one cycle before dropping
        SetPwm(currentPosition);
}

ServoL::ServoL(bool leftServo)
{
    velocity = MIN_VELOCITY;
    maxVelocity = MAX_VELOCITY;
    minVelocity = MIN_VELOCITY;
    currentPosition = (SERVO_MIN_MS + SERVO_MAX_MS) / 2;
    done = true;
}

void ServoL::GoToPosition()
{
    CalculateVelocity();
    if (!done)
    {
        // this->currentPosition+=((this->currentPosition-this->msPosition)/300);
        if (this->currentPosition > this->msPosition)
            this->currentPosition -= this->velocity;
        else
            this->currentPosition += this->velocity;

        // if(currentPosition - msPosition < velocity &&
        //    currentPosition - msPosition > -velocity)
        if (IS_BETWEEN(currentPosition - msPosition, -velocity, velocity))
            this->currentPosition = this->msPosition;

        // Move servo
        WriteMs();

        // If the servo has reached the final position move is done
        if (this->currentPosition == this->msPosition)
            done = true;
    }
}

void ServoL::ChangeVelocityLimits(int v)
{
    minVelocity = v;
    maxVelocity = 3 * v + 5;
}
void ServoL::CalculateVelocity()
{
    // if(currentPosition - msPosition < DISTANCE_DECCELERATION &&
    //     currentPosition - msPosition > - DISTANCE_DECCELERATION )
    if (IS_BETWEEN(currentPosition - msPosition, -DISTANCE_DECCELERATION, DISTANCE_DECCELERATION))
    {
        // deccelerate
        velocity -= DECCELERATION;
    }
    else
    {
        // accelerate
        velocity += ACCELERATION;
    }

    if (velocity < minVelocity)
        velocity = minVelocity;
    if (velocity > maxVelocity)
        velocity = maxVelocity;
}
void ServoL::ChangePosition(uint8_t pos)
{
    msPosition = map(pos, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS);
    position = pos;
    done = false;
}
void ServoL::Write(uint8_t newPosition)
{
    if (newPosition <= 180 && newPosition >= 0)
    {
        this->position = newPosition;
        this->msPosition = map(this->position, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS);
        currentPosition = msPosition;
        WriteMs();
    }
}
const uint16_t& ServoL::GetPwmValue()
{
    return pwmValue;
}



