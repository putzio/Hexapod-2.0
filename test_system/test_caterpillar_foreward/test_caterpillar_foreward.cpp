#include <stdio.h>
#include "pico/stdlib.h"
#include "servo_left.hpp"
#include "leg_controller.hpp"
#include "gaitController.hpp"
#include "gpio.hpp"

void UpdateServoPositions(std::array<pico_drivers::ServoLeft, 12>& servos, std::array<logic::leg::ServosPositions, 6>& servoPositions) {
    for (int i = 0; i < servoPositions.size(); i++) {
        servos[2 * i].SetRadianAngle(servoPositions[i].upperServoAngle);
        servos[2 * i + 1].SetRadianAngle(servoPositions[i].lowerServoAngle);
    }
}



int main() {
    stdio_init_all();
    pico_drivers::Gpio led = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
    led.Write(true);
    std::array<uint8_t, 12> pins;
    for (int i; i < pins.size(); i++) {
        pins[i] = i + 2;
    }
    printf("Start\r\n");
    sleep_ms(2000);
    printf("Init\r\n");
    sleep_ms(2000);
    pico_drivers::LegController legController = pico_drivers::LegController(pins);
    legController.InitServos();
    logic::GaitController gaitController = logic::GaitController();
    sleep_ms(500);
    printf("Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    printf("ChangeGait result: %d\r\n", gaitController.ChangeGait(logic::gait::GaitInterface::CATERPILLAR));
    printf("changing step values:\t%f\t%f\r\n", gaitController.p_ptr_gaitInterface->GetChangingStepValues()[0], gaitController.p_ptr_gaitInterface->GetChangingStepValues()[1]);
    printf("Leg changing steps: %f, %f\r\n", gaitController.legs[0].GetChangingStepInAir(), gaitController.legs[1].GetChangingStepOnGround());
    // sleep_ms(500);
    // printf("Tripod, Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    printf("ChangeDirection result: %d\r\n", gaitController.ChangeDirection(logic::GaitController::FOREWARD));
    // sleep_ms(500);
    // printf("Foreward, Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    gaitController.ResetLegTargetPositions();

    printf("changing step values:\t%f\t%f\r\n", gaitController.p_ptr_gaitInterface->GetChangingStepValues()[0], gaitController.p_ptr_gaitInterface->GetChangingStepValues()[1]);
    printf("Leg changing steps: %f, %f\r\n", gaitController.legs[0].GetChangingStepInAir(), gaitController.legs[1].GetChangingStepOnGround());
    // sleep_ms(500);
    // printf("Reset, Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    legController.UpdateServos(gaitController.GetSerovAngles());
    // printf("Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    // sleep_ms(2000);
    // printf("Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
    sleep_ms(2000);
    while (1) {
        sleep_ms(50);
        // printf("Hello, world!\n");
        led.Toggle();
        printf("PP Result: %d\r\n", gaitController.PeriodicProcess());
        printf("X coordiante leg0: %f\r\n", gaitController.legs[0].p_controller.GetCoordinates().x.GetCoordinate_mm());
        legController.UpdateServos(gaitController.GetSerovAngles());
        printf("upper angle: %f \r\n", gaitController.legs[0].p_servos.GetCurrentServoPositions().upperServoAngle);
        printf("lower angle: %f \r\n", gaitController.legs[0].p_servos.GetCurrentServoPositions().lowerServoAngle);
        printf("Get gait: %d\r\n", gaitController.p_ptr_gaitInterface->GetCurrentGait());
        // printf("Get direction: %d\r\n", gaitController.p_ptr_gaitInterface-);
        printf("x: %f mm\r\n", gaitController.targetLegsPositions->legs[0].x.GetCoordinate_mm());
        printf("foot on ground: %d \r\n", gaitController.targetLegsPositions->legs[0].footOnGround);
        printf("Step: %d\r\n", gaitController.p_ptr_gaitInterface->step);
        printf("Changing step: %f\r\n", gaitController.legs[0].GetChangingStep());
    }
}