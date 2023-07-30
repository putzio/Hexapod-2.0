#include "ssi.hpp"

// SSI tags - tag length limited to 8 bytes by default
const char* ssi_tags[] = { "s1", "s2", "s3", "s4","s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "servo" };
volatile int16_t calibration_values[12] = { 0 };
volatile uint8_t calibratingServoIndex = 0;

u16_t ssi_handler(int iIndex, char* pcInsert, int iInsertLen) {
    size_t printed;
    switch (iIndex) {
    case 12: // leg
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibratingServoIndex);
        break;
    }
    default:
        if (iIndex >= 0 && iIndex < 12)
            printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[iIndex]);
        else
            printed = 0;
        break;
    }

    return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
