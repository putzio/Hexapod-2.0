#include "Logic/SlaveServo.hpp"
// #include "pico/double.h"
#include "cmath"


SlaveServo::SlaveServo(bool leftServo, bool sBack)
    : ServoL(leftServo)
{
    slaveBack = sBack;
}
uint8_t SlaveServo::Calculate(int masterPosition)
{
    float alfa = masterPosition - 90.0;
    if (alfa < 0)
        alfa = -alfa;
    float rad = 3.1415 / 180.0;
    float sinPosNAlfa = (h - cos((float)alfa * rad));
    // position = asin(sinPosNAlfa)/rad - alfa;
    // float calculatedH = cos(alfa * rad) + sin((position + alfa) * rad);
    // sinPosNAlfa += (h - calculatedH);
    if (slaveBack)
        position = asin(sinPosNAlfa) / rad - alfa;
    else
        position = 180.0 - asin(sinPosNAlfa) / rad + alfa;
    return position;
}
// sets SlaveServo at the right position, so the leg heigth does not change
void SlaveServo::SlavePosition(float masterPosition)
{
    if (enableSlave)
    {
        position = Calculate(masterPosition);
        Write(position);
    }
}