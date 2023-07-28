#pragma once
#include "pico/stdlib.h"
#include "cgi.hpp"
#include "wifi_passwords.hpp"

namespace web {
    class Server {
    public:
        Server(std::vector <tCGI>& cgiHandlers);
        // private:
        //     CGI cgi;
    };
}