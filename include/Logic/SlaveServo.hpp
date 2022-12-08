#include "ServoL.hpp"
#include "Result.hpp"

#define DEFAULT_HIGHT 17000 // max = 1,76, min = 1,5???
#define PI 3.1415

class SlaveServo : public ServoL
{
public:
    enum ServoPosition
    {
        slaveForward,
        slaveBack
    };
private:
    ServoPosition servoPosition = slaveBack;
    uint16_t hight = DEFAULT_HIGHT;
    uint8_t CalculatePosition(int masterPosition);

public:
    bool enableSlave = false;//CHECK
    SlaveServo(ServoSide side = rightServo, ServoPosition position = slaveForward);    
    // sets SlaveServo at the right position, so the leg heigth does not change
    void UpdateSlavePosition(uint8_t masterPosition);
    Result ChangeHight(uint16_t newHight);
    uint16_t GetHight();
};