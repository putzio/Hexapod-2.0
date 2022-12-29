#include "Logic/SlaveServo.hpp"
// #include "pico/double.h"
#include "cmath"
#include <iostream>


SlaveServo::SlaveServo(ServoSide side, ServoPosition position)
    : ServoL(side)
{
    servoPosition = position;
}
uint8_t SlaveServo::CalculatePosition(int masterPosition)
{
    float alfa = masterPosition - 90.0;
    if (alfa < 0)
        alfa = -alfa;
    float rad = PI / 180.0;
    float sinPosNAlfa = (((float) hight / 10000.0) - cos((float)alfa * rad));
    // position = asin(sinPosNAlfa)/rad - alfa;
    // float calculatedH = cos(alfa * rad) + sin((position + alfa) * rad);
    // sinPosNAlfa += (h - calculatedH);
    std::cout<<"Sin: "<<sinPosNAlfa;
    std::cout<<"SBack: "<<slaveBack;
    if (servoPosition)
        position = asin(sinPosNAlfa) / rad - alfa;
    else
        position = 180.0 - asin(sinPosNAlfa) / rad + alfa;
    std::cout<< "Pos: "<<(uint16_t)position;
    return position;
}
// sets SlaveServo at the right position, so the leg heigth does not change
void SlaveServo::UpdateSlavePosition(uint8_t masterPosition)
{
    if (enableSlave)
    {
        position = CalculatePosition(masterPosition);
        Write(position);
    }
}

//bool? Result?
Result SlaveServo::ChangeHight(uint16_t newHight)
{
    if(newHight > 10000 && newHight < 19000)//CHECK
    {
        hight = newHight;
        return kOkResult;
    }
    return kHightOutOfRange;
}

uint16_t SlaveServo::GetHight()
{
    return hight;
}

