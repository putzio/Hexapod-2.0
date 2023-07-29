#pragma once
#include "pico/stdlib.h"
#include "cgi.hpp"
#include "wifi_passwords.hpp"

namespace web {
    class Server {
    public:
        Server();
        void Run(std::vector <tCGI>& cgiHandlers);
    private:
        CGI cgi;
    };
}