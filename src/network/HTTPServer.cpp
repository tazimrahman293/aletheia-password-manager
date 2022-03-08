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
#include "network/HTTPServer.h"

#include "events/LoginAttemptEvent.h"
#include "events/LogoutEvent.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "events/AccountDeleteEvent.h"


/**
 * Helper function for returning an object parsed by the json utility
 * @tparam T the type of record object to be generated
 * @param body a string of valid JSON
 * @return an object of type T with member variables set to the fields in the JSON
 */
template<class T>
T parseRecordFromJSON(std::string body)
{
    using json = nlohmann::json;
    auto data = json::parse(body);
    return data.get<T>();
}


/**
 * Helper function for publishing a new Event to the Event Bus
 * @tparam EventType the type of event to be published
 * @tparam ArgType the types of the variadic arguments
 * @param args variadic arguments to be passed as parameters to the Event constructor
 */
template<class EventType, class... ArgType>
void publishEvent(ArgType... args)
{
    EventBus *eventBus = EventBus::GetInstance();
    eventBus->Publish(new EventType(args...));
}


/**
 * Initializes the HTTP server instance by setting up all the available API endpoints.
 */
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
                auto data = json::parse(request.body);
                int uid = data["uid"].get<int>();
                std::string pass = data["pass"].get<std::string>();

                publishEvent<LoginAttemptEvent>(uid, pass);

                // TODO Respond after the login is validated (or invalidated)
                response.set_content("TODO: Implement this!", "text/plain");
            });

    // User logout
    server.Get(
            "/logout",
            [](const Request& request, Response& response) -> void
            {
                publishEvent<LogoutEvent>();
            });

    // Create new account
    server.Post(
            "/new-account",
            [](const Request& request, Response& response) -> void
            {
                auto record = parseRecordFromJSON<Account>(request.body);
                publishEvent<AccountCreateEvent>(record);
            });

    // Edit existing account
    server.Post(
            "/edit-account",
            [](const Request& request, Response& response) -> void
            {
                auto record = parseRecordFromJSON<Account>(request.body);
                publishEvent<AccountUpdateEvent>(record);
            });

    // Remove account
    server.Post(
            "/remove-account",
            [](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                auto id = data["id"].get<int>();
                publishEvent<AccountDeleteEvent>(id);
            });
}


/**
 * Runs the main listen loop for the HTTP server.
 */
void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    server.listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
