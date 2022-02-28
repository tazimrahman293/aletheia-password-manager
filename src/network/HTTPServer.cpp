//
// Created by jeremy on 2022-02-27.
//

#include <cassert>
#include <iostream>
#include <string>

#include <httplib.h>
#include <json.h>

#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
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
                using json = nlohmann::json;

                EventBus *eventBus = EventBus::GetInstance();

                auto data = json::parse(request.body);
                int uid = data["uid"].get<int>();
                std::string pass = data["pass"].get<std::string>();

                eventBus->Publish(new LoginAttemptEvent(uid, pass));

                // TODO Respond after the login is validated (or invalidated)
                response.set_content("TODO: Implement this!", "text/plain");
            });
}


void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    server.listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
