#include "cgi.hpp"

namespace web {
    CGI::CGI(std::vector <tCGI>& cgiHandlers) {
        printf("CGI constructor\n");
        http_set_cgi_handlers((const tCGI*)cgiHandlers.data(), cgiHandlers.size());
    }
}

