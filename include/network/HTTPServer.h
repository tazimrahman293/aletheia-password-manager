//
// Created by jeremy on 2022-02-25.
//

#ifndef PROJECT_HTTPSERVER_H
#define PROJECT_HTTPSERVER_H

#include <httplib.h>
#include "Storage.h"


/**
 * Wraps the httplib server functionality and defines endpoints for the network API.
 */
class HTTPServer : private httplib::Server {

    // The hostname/IP to accept connections on
    std::string hostAddress;

    // The port number on which to open a socket
    int hostPort;

    // Handle for the storage instance (database)
    Storage *storage = nullptr;

    httplib::Headers defaultHeaders = {
            {"Access-Control-Allow-Origin", "*"},
            {"Access-Control-Allow-Headers", "*"}
    };

public:

    HTTPServer(std::string address, int port) :
        httplib::Server(), hostAddress(std::move(address)), hostPort(port) { }
    explicit HTTPServer(int port) : HTTPServer("0.0.0.0", port) { }
    HTTPServer() : HTTPServer(8089) { }

    HTTPServer(HTTPServer& other) = delete;  // No copying
    void operator=(HTTPServer& other) = delete;  // No assignment

    void Init(Storage *store);
    void Run();

};

#endif //PROJECT_HTTPSERVER_H
