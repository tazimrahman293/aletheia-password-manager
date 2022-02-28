//
// Created by jeremy on 2022-02-27.
//

#include <cassert>
#include <iostream>

#include <httplib.h>

#include "network/HTTPServer.h"


void HTTPServer::Init()
{
    assert(hostPort > 1023 && hostPort <= 65535 && "Port must be between 1024 and 65535");

    using namespace httplib;

    server.Get(
            "/hello",
            [](const Request& request, Response& response) -> void
            {
                response.set_content("Hello, world!", "text/plain");
            });

    server.Post(
            "/login",
            [](const Request& request, Response& response) -> void
            {
                if (request.is_multipart_form_data()) {
                    auto dataUID = request.get_file_value("uid");
                    auto dataPass = request.get_file_value("pass");
                }
            });
}


void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    server.listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
