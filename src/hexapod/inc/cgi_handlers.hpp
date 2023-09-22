#pragma once
#include "hexapod.hpp"
#include "cgi.hpp"
#include <string>

const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_calibration_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_ground_detection(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);