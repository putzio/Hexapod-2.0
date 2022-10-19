#pragma once
#include "enum_types.h"
void ADC_INIT();
bool MeasureBattery();
void Message(bool& changeVelocity, bool& velocityChanged, int& velocity, enum Mode& mode, char& recMode);