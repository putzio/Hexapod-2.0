#include "Logic/ServoVelocity.hpp"

#define IS_BETWEEN(x, min, max) (x > min && x < max)

ServoVelocity::ServoVelocity()
{
    velocity = MIN_VELOCITY;
    maxVelocity = MAX_VELOCITY;
    minVelocity = MIN_VELOCITY;
}

void ServoVelocity::ChangeVelocityLimits(int v){
    minVelocity = v;
    maxVelocity = 3 * v + 5;
}
void ServoVelocity::CalculateVelocity(int16_t distance){
    // if(currentPosition - msPosition < DISTANCE_DECCELERATION &&
    //     currentPosition - msPosition > - DISTANCE_DECCELERATION )
    if (IS_BETWEEN(distance, -DISTANCE_DECCELERATION, DISTANCE_DECCELERATION))
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