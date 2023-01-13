#pragma once

#include "Logic/LegPositionController.hpp"
#include "Logic/Servos_struct.hpp"
#include "constants.hpp"

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
    Side p_side; // in servo hardware?
    Side p_elbow; //different LegPositionController classes?
    Coordinates p_finalTargetPostion;
    bool p_legUp;

    Coordinates CalculateNewCoordinates(Coordinates &coordinates);
    bool LegInFinalTargetPosition(const Coordinates &coordinates);
    public:
    // static const uint8_t c_LEG_LENGTH = 70;//mm 

    public:
    Leg(Side side, Side elbow);
    Leg(Side side, Side elbow, Servos &servos, LegPositionController &controller);

    void MoveLegToTheXYTarget(const Coordinates &coordinates);
    Result LegPeriodicProcess();   //TEst???

    void SetNewTargetPosition(const Coordinates &coordinates, bool legUp);

    const Servos* const GetServosPtr()const;
};