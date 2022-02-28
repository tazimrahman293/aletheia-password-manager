//
// Created by jeremy on 2022-02-27.
//

#include <cassert>
#include <iostream>
#include <string>

#include <httplib.h>
#include <json.h>

#include "data/Account.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"


void HTTPServer::Init()
{
    assert(hostPort > 1023 && hostPort <= 65535 && "Port must be between 1024 and 65535");

    using namespace httplib;
    using json = nlohmann::json;

    // For testing purposes
    server.Get(
            "/hello",
            [](const Request& request, Response& response) -> void
            {
                response.set_content("Hello, world!", "text/plain");
            });

    // User login attempt
    server.Post(
            "/login",
            [](const Request& request, Response& response) -> void
            {
                EventBus *eventBus = EventBus::GetInstance();

                auto data = json::parse(request.body);
                int uid = data["uid"].get<int>();
                std::string pass = data["pass"].get<std::string>();

                eventBus->Publish(new LoginAttemptEvent(uid, pass));

                // TODO Respond after the login is validated (or invalidated)
                response.set_content("TODO: Implement this!", "text/plain");
            });

    // Create new account
    server.Post(
            "/new-account",
            [](const Request& request, Response& response) -> void
            {
                EventBus *eventBus = EventBus::GetInstance();

                auto data = json::parse(request.body);
                auto record = data.get<Account>();

                eventBus->Publish(new AccountCreateEvent(record));
            });

    // Edit existing account
    server.Post(
            "/edit-account",
            [](const Request& request, Response& response) -> void
            {
                EventBus *eventBus = EventBus::GetInstance();

                auto data = json::parse(request.body);
                auto record = data.get<Account>();

                eventBus->Publish(new AccountUpdateEvent(record));
            });
}


void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    server.listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
