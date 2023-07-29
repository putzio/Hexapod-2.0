#include "cgi_handlers.hpp"

extern Hexapod hexapod;

const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
    printf("cgi_direction_handler\n");
    if (strcmp(pcParam[0], "direction") == 0) {
        if (strcmp(pcValue[0], "forward") == 0)
            hexapod.SetDirection(logic::GaitController::Direction::FORWARD);
        else if (strcmp(pcValue[0], "backward") == 0)
            hexapod.SetDirection(logic::GaitController::Direction::BACKWARD);
        else if (strcmp(pcValue[0], "left") == 0)
            hexapod.SetDirection(logic::GaitController::Direction::TURN_LEFT);
        else if (strcmp(pcValue[0], "right") == 0)
            hexapod.SetDirection(logic::GaitController::Direction::TURN_RIGHT);
        else if (strcmp(pcValue[0], "stop") == 0)
            hexapod.SetDirection(logic::GaitController::Direction::STOP);
        else {
            printf("Unknown direction\n");
        }

    }
    // Send the index page back to the user
    return "/index.shtml";
}

const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
    printf("cgi_gait_handler\n");

    if (strcmp(pcParam[0], "gait") == 0) {

        if (strcmp(pcValue[0], "tripod") == 0)
            hexapod.SetGait(logic::gait::Gait::TRIPOD);
        else if (strcmp(pcValue[0], "caterpillar") == 0)
            hexapod.SetGait(logic::gait::Gait::CATERPILLAR);
        else if (strcmp(pcValue[0], "monochromatic") == 0)
            hexapod.SetGait(logic::gait::Gait::MONOCHROMATIC);
        else if (strcmp(pcValue[0], "none") == 0)
            hexapod.SetGait(logic::gait::Gait::NONE);
        else {
            printf("Unknown gait\n");
        }
    }

    // Send the index page back to the user
    return "/index.shtml";
}
const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
    printf("cgi_speed_handler\n");

    if (strcmp(pcParam[0], "speed") == 0) {
        hexapod.SetSpeed(std::stoi(pcValue[0]));
    }

    // Send the index page back to the user
    return "/index.shtml";
}