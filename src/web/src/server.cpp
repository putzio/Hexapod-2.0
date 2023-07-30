#include "server.hpp"

namespace web {
    Server::Server() {
        printf("Server constructor\n");
        cyw43_arch_init();
        cyw43_arch_enable_sta_mode();

        // Connect to the WiFI network - loop until connected
        while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0) {
            printf("Attempting to connect...\n");
        }
        // Print a success message once connected
        printf("Connected! \n");
    }
    void Server::Run(std::vector <tCGI>& cgiHandlers) {

        // Initialise web server
        httpd_init();
        printf("Http server initialised\n");
        // // Configure SSI and CGI handler
        ssi_init();
        printf("SSI Handler initialised\n");
        web::CGI cgi = web::CGI(cgiHandlers);
        printf("CGI Handler initialised\n");
    }
}