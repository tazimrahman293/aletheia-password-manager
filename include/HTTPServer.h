//
// Created by jeremy on 2022-02-25.
//

#ifndef PROJECT_HTTPSERVER_H
#define PROJECT_HTTPSERVER_H


#include <httplib.h>

class HTTPServer {

};


void test_server()
{
    httplib::Server server;

    server.Get("/hello", [](const httplib::Request& request, httplib::Response& response) {
        response.set_content("Hello, world!", "text/plain");
    });

    server.listen("0.0.0.0", 8080);
}


#endif //PROJECT_HTTPSERVER_H
