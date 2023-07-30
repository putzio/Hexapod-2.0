#pragma once
#include "lwip/apps/httpd.h"
#include "gpio_w.hpp"
#include <vector>

// namespace web {
//     class SSI {
//     public:
//         SSI() {}
//         SSI(std::vector <tCGI>& ssiHandlers);
//     };
// }

// SSI tags - tag length limited to 8 bytes by default
extern const char* ssi_tags[];

u16_t ssi_handler(int iIndex, char* pcInsert, int iInsertLen);

// Initialise the SSI handler
void ssi_init();