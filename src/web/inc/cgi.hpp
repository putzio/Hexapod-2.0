#pragma once

#include "lwip/apps/httpd.h"
#include "gpio_w.hpp"
#include <vector>

namespace web {
    class CGI {
    public:
        CGI() {}
        CGI(std::vector <tCGI>& cgiHandlers);
        
    };
}