#include "ssi.hpp"

// SSI tags - tag length limited to 8 bytes by default
const char* ssi_tags[] = { "s1", "s2", "s3", "s4","s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12" };
volatile int16_t calibration_values[12] = { 0 };

u16_t ssi_handler(int iIndex, char* pcInsert, int iInsertLen) {
    size_t printed;
    switch (iIndex) {
    case 0: // s1
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[0]);
        break;
    }
    case 1: // s2
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[1]);
        break;
    }
    case 2: // s3
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[2]);
        break;
    }
    case 3: // s4
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[3]);
        break;
    }
    case 4: // s5
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[4]);
        break;
    }
    case 5: // s6
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[5]);
        break;
    }
    case 6: // s7
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[6]);
        break;
    }
    case 7: // s8
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[7]);
        break;
    }
    case 8: // s9
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[8]);
        break;
    }
    case 9: // s10
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[9]);
        break;
    }
    case 10: // s11
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[10]);
        break;
    }
    case 11: // s12
    {
        printed = snprintf(pcInsert, iInsertLen, "%d", calibration_values[11]);
        break;
    }
    default:
        printed = 0;
        break;
    }

    return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
