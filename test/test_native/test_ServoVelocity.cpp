#include "Logic/ServoVelocity.hpp"
#include "gtest/gtest.h"

TEST(ServoVelocity, test_initialises_Servo_Velocity){
    // initialise the right servo
    ServoVelocity velocity;
    ASSERT_EQ(MIN_VELOCITY, velocity.velocity);
}

TEST(ServoVelocity, test_calculates_servo_velocity)
{
    ServoVelocity velocity;
    
    int16_t distance = 0;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(MIN_VELOCITY, velocity.velocity);

    distance = DISTANCE_DECCELERATION + 1;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(float(MIN_VELOCITY + ACCELERATION), velocity.velocity);

    distance = 0;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(MIN_VELOCITY, velocity.velocity);
    
    velocity.velocity = MAX_VELOCITY;
    distance = DISTANCE_DECCELERATION + 2;
    ASSERT_EQ(MAX_VELOCITY,velocity.velocity);
}
TEST(ServoVelocity, test_change_velocity)
{
    ServoVelocity velocity;
    int16_t v = 10;
    velocity.ChangeVelocityLimits(v);
    ASSERT_EQ(v, velocity.minVelocity);

    v = v * 3 + 5;
    ASSERT_EQ(v, velocity.maxVelocity);
}