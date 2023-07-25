#include "cgi.hpp"

namespace web {
    pico_drivers::Gpio_w CGI::led = pico_drivers::Gpio_w();
    CGI::CGI() {
        printf("CGI constructor\n");

        cgiHandlers_ptr = new tCGI[4];
        cgiHandlers_ptr[0] = { "/led.cgi", (tCGIHandler)CGI::cgi_led_handler };
        cgiHandlers_ptr[1] = { "/direction.cgi", (tCGIHandler)CGI::cgi_direction_handler };
        cgiHandlers_ptr[2] = { "/gait.cgi", (tCGIHandler)CGI::cgi_gait_handler };
        cgiHandlers_ptr[3] = { "/speed.cgi", (tCGIHandler)CGI::cgi_speed_handler };
        http_set_cgi_handlers(cgiHandlers_ptr, 4);
    }
    const char* CGI::cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
        printf("cgi_led_handler\n");
        // Check if an request for LED has been made (/led.cgi?led=x)
        if (strcmp(pcParam[0], "led") == 0) {
            // Look at the argument to check if LED is to be turned on (x=1) or off (x=0)
            if (strcmp(pcValue[0], "0") == 0) {
                led.Write(0);
            }
            else if (strcmp(pcValue[0], "1") == 0)
                led.Write(1);
        }
        // Send the index page back to the user
        return "/index.shtml";
    }
    const char* CGI::cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
        printf("cgi_direction_handler\n");
        if (strcmp(pcParam[0], "direction") == 0) {
            if (strcmp(pcValue[0], "forward") == 0)
                led.Write(0);
            else if (strcmp(pcValue[0], "backward") == 0)
                led.Write(1);
            else if (strcmp(pcValue[0], "left") == 0)
                led.Write(0);
            else if (strcmp(pcValue[0], "right") == 0)
                led.Write(1);

        }
        // Send the index page back to the user
        return "/index.shtml";
    }

    const char* CGI::cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
        printf("cgi_gait_handler\n");

        if (strcmp(pcParam[0], "gait") == 0) {

            if (strcmp(pcValue[0], "tripod") == 0)
                led.Write(0);
            else if (strcmp(pcValue[0], "caterpillar") == 0)
                led.Write(1);
            else if (strcmp(pcValue[0], "monochromatic") == 0)
                led.Write(0);
        }

        // Send the index page back to the user
        return "/index.shtml";
    }
    const char* CGI::cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
        printf("cgi_speed_handler\n");

        if (strcmp(pcParam[0], "speed") == 0) {
            printf(pcValue[0]);
        }

        // Send the index page back to the user
        return "/index.shtml";
    }
}

