#include "ServoL.hpp"

#define h 1.7 // max = 1,76, min = 1,5???

class SlaveServo : public ServoL
{
private:
    bool slaveBack = true;

public:
    bool enableSlave = false;
    SlaveServo(bool leftServo = false, bool sBack = false);
    uint8_t Calculate(int masterPosition);
    // sets SlaveServo at the right position, so the leg heigth does not change
    void SlavePosition(float masterPosition);
};