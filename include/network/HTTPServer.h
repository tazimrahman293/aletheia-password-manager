//
// Created by jeremy on 2022-02-25.
//

#ifndef PROJECT_HTTPSERVER_H
#define PROJECT_HTTPSERVER_H

#include <httplib.h>


class HTTPServer {

    // The actual server instance for handling requests
    httplib::Server server;

    // The hostname/IP to accept connections on
    std::string hostAddress;

    // The port number on which to open a socket
    int hostPort;

public:

    HTTPServer(std::string address, int port) : hostAddress(std::move(address)), hostPort(port) { }
    explicit HTTPServer(int port) : HTTPServer("0.0.0.0", port) { }
    HTTPServer() : HTTPServer(8089) { }
    ~HTTPServer() = default;

    HTTPServer(HTTPServer& other) = delete;  // No copying
    void operator=(HTTPServer& other) = delete;  // No assignment

    void Init();
    void Run();

};

#endif //PROJECT_HTTPSERVER_H
