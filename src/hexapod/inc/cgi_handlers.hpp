#pragma once
#include "hexapod.hpp"
#include "cgi.hpp"
#include <string>

static const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
static const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
static const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
static const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);