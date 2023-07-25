#pragma once

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "gpio_w.hpp"

namespace web {
    class CGI {
    public:
        CGI();
        ~CGI() { delete cgiHandlers_ptr; };
        void cgi_init(void);
    private:
        static pico_drivers::Gpio_w led;
        tCGI* cgiHandlers_ptr;
        static const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
        static const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
        static const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
        static const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
    };
}