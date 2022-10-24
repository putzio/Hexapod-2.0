#pragma once

#include <stdio.h>
#include <stdint.h>
#include "BasicServo.hpp"
#include "Logic/ServoVelocity.hpp"

// ServoL motion parameters
#define SERVO_MIN_MS 550  // time in microseconds for 0 degrees
#define SERVO_MAX_MS 2400 // time in microseconds for 180 degrees
#define CYCLE_TIME 20     // ms
#define ACCELLERATION_PER_S 50.0
#define ACCELERATION 0.2 // ACCELERATION_PER_S*CYCLE_TIME *(SERVO_MAX_MS - SERVO_MIN_MS)/180
#define DECCELERATION 1
#define MAX_VELOCITY 20 // 20/(2400-550)/0.02 = 97*/s //in datasheet max speed -> 60*/0.1s = 600*/s
#define MIN_VELOCITY 1
#define DISTANCE_DECCELERATION 200
#define POS_90_TIME 200 // time for the leg to move to 90* before the next starts to move (to lower the current)

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define IS_BETWEEN(x, min, max) (x > min && x < max)

uint16_t map(float x, uint16_t sMin, uint16_t sMax, uint16_t dMin, uint16_t dMax);

class ServoL: public BasicServo, public ServoVelocity 
{
private:
    uint16_t pwmValue;
    void SetPwm(uint16_t value);
    friend class TestServo;
protected:
    bool left = false; // if the servo is on the other side it has to move the opposite way -> left = true
    // msPosition:
    // calculated from position in the Write() method of destination
    //      OR
    // Changes value in the ChangePosition() method and then moves servo from currentPosition
    // to the changed one by using GoToPosition() method
    volatile uint16_t msPosition;
    // float velocity;  // is changed and calculated in CalculateVelocity() method
    // int maxVelocity; // privte?
    // int minVelocity;
    uint16_t CalculateLeft(uint16_t pos);
    void WriteMs();

public:
    bool done;
    float position; // position given by the user

    ServoL(bool leftServo = false);
    void GoToPosition();

    // void ChangeVelocityLimits(int v);
    // void CalculateVelocity();

    void ChangePosition(uint8_t pos);
    void Write(uint8_t newPosition);
    const uint16_t& GetPwmValue();
};