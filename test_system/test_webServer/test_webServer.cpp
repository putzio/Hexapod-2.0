#include "pico/stdlib.h"
#include "server.hpp"

// WIFI Credentials - take care if pushing to github!
web::Gpio_w led;

const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

int main() {
    stdio_init_all();

    std::vector <tCGI> cgiHandlers;
    cgiHandlers.push_back(tCGI{ "/led.cgi", (tCGIHandler)cgi_led_handler });
    cgiHandlers.push_back(tCGI{ "/direction.cgi", (tCGIHandler)cgi_direction_handler });
    cgiHandlers.push_back(tCGI{ "/gait.cgi", (tCGIHandler)cgi_gait_handler });
    cgiHandlers.push_back(tCGI{ "/speed.cgi", (tCGIHandler)cgi_speed_handler });
    // // Configure SSI and CGI handler
    // ssi_init();
    // printf("SSI Handler initialised\n");
    web::Server server = web::Server();
    led = web::Gpio_w();
    server.Run(cgiHandlers);

    // Infinite loop
    while (1);
}

const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
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
const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
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

const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
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
const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]) {
    printf("cgi_speed_handler\n");

    if (strcmp(pcParam[0], "speed") == 0) {
        printf(pcValue[0]);
    }

    // Send the index page back to the user
    return "/index.shtml";
}