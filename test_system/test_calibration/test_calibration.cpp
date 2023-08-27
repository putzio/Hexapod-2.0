
#include <stdio.h>
#include "cgi.hpp"
#include "wifi_passwords.hpp"
#include "legs_controller.hpp"
#include "pinout.hpp"
#include "ssi.hpp"

// WIFI Credentials - take care if pushing to github!
// const char WIFI_SSID[] = "xdddd";
// const char WIFI_PASSWORD[] = "kapusta15";
web::Gpio_w led;
uint8_t leg = 0;
extern volatile int16_t calibration_values[12];

const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_direction_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_gait_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_speed_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

int main() {
    stdio_init_all();

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    // Connect to the WiFI network - loop until connected
    while (cyw43_arch_wifi_connect_timeout_ms(web::WIFI_SSID, web::WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0) {
        printf("Attempting to connect...\n");
    }
    // Print a success message once connected
    printf("Connected! \n");

    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    std::vector <tCGI> cgiHandlers;
    cgiHandlers.push_back(tCGI{ "/led.cgi", (tCGIHandler)cgi_led_handler });
    cgiHandlers.push_back(tCGI{ "/direction.cgi", (tCGIHandler)cgi_direction_handler });
    cgiHandlers.push_back(tCGI{ "/gait.cgi", (tCGIHandler)cgi_gait_handler });
    cgiHandlers.push_back(tCGI{ "/speed.cgi", (tCGIHandler)cgi_speed_handler });

    led = web::Gpio_w();
    // // Configure SSI and CGI handler
    ssi_init();
    printf("SSI Handler initialised\n");
    web::CGI cgi = web::CGI(cgiHandlers);
    printf("CGI Handler initialised\n");
    std::array<uint8_t, 12> pins;
    for (int i = 0; i < 12; i++) {
        pins[i] = i + FIRST_SERVO_PIN;
    }
    pico_drivers::LegsController legsController = pico_drivers::LegsController(pins);
    legsController.InitServos();
    // Infinite loop
    while (1) {
        for (int i = 0; i < 12; i++) {
            legsController.CalibrateServo(i, calibration_values[i]);
        }
        legsController.InitServos();
        sleep_ms(250);
    }
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
        if (strcmp(pcValue[0], "forward") == 0) {
            led.Write(0);
            leg++;
            if (leg > 11) {
                leg = 0;
            }
            printf("leg: %d\n", leg);
        }
        else if (strcmp(pcValue[0], "backward") == 0) {
            led.Write(1);
            leg--;
            if (leg > 11) {
                leg = 11;
            }
            printf("leg: %d\n", leg);
        }
        else if (strcmp(pcValue[0], "left") == 0) {
            led.Write(0);
            calibration_values[leg] -= 10;
            printf("calibration_values[%d]: %d\n", leg, calibration_values[leg]);
        }
        else if (strcmp(pcValue[0], "right") == 0) {
            led.Write(1);
            calibration_values[leg] += 10;
            printf("calibration_values[%d]: %d\n", leg, calibration_values[leg]);
        }

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
        else if (strcmp(pcValue[0], "metachromatic") == 0)
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
