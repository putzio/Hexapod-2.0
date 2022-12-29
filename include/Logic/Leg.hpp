#pragma once

#include "Logic/LegPositionController.hpp"
#include "Logic/Servos_struct.hpp"
#include "memory"

enum Side:uint8_t{
    UNDEFINED,
    LEFT,
    RIGHT,
    ELBOW_BACK,
    ELBOW_FRONT
};


class Leg{
    private:
    Servos p_servos;
    LegPositionController p_controller;
    Side p_side;
    Side p_elbow;

    public:
    const uint8_t c_LEG_LENGTH = 70;//mm 

    public:
    Leg(Side side, Side elbow);
    Leg(Side side, Side elbow, Servos &servos, LegPositionController &controller);

    void MoveLegToTheXYTarget(const Coordinates &coordinates);
    void LegPeriodicProcess();   //TEst???

    const Servos* const GetServosPtr()const;
};