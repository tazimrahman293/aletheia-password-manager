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
void HTTPServer::Init(Storage *store)
{
    assert(hostPort > 1023 && hostPort <= 65535 && "Port must be between 1024 and 65535");

    this->storage = store;

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
            [this](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                int uid;
                std::string pass;
                try {
                    uid = data.at("uid").get<int>();
                    pass = data.at("pass").get<std::string>();
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                // publishEvent<LoginAttemptEvent>(uid, pass);
                auto user = storage->GetByID<User>(uid);

                if (user != nullptr) {
                    // TODO hash password/key to check if valid login
                    if (pass.empty()) {  // TODO or other problems with the formation of the password, or if invalid
                        response.status = 401;
                        return;
                    }

                    json j = *user;
                    j.erase("keyHash");  // Not really a threat to include this but best to be careful anyway

                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 401;
                }
            });

    // User logout
    server.Get(
            "/logout",
            [this](const Request& request, Response& response) -> void
            {
                // TODO What happens here?
                // publishEvent<LogoutEvent>();
            });

    // Create new account
    server.Post(
            "/new-account",
            [this](const Request& request, Response& response) -> void
            {
                auto record = parseRecordFromJSON<Account>(request.body);
                // publishEvent<AccountCreateEvent>(record);

                storage->Insert(record);

                if (record.pk > 0) {
                    json j = record;
                    j.erase("keyHash");

                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 500;
                    response.set_content("Unable to store new Account record.", "text/plain");
                }
            });

    // Edit existing account
    server.Post(
            "/edit-account",
            [this](const Request& request, Response& response) -> void
            {
                auto record = parseRecordFromJSON<Account>(request.body);
                // publishEvent<AccountUpdateEvent>(record);

                storage->Update(record);

                if (record.pk > 0) {
                    json j = record;
                    j.erase("keyHash");

                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 500;
                    response.set_content("Unable to edit Account record.", "text/plain");
                }
            });

    // Remove account
    server.Post(
            "/remove-account",
            [this](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                auto id = data["id"].get<int>();
                // publishEvent<AccountDeleteEvent>(id);

                storage->Remove<Account>(id);

                response.status = 200;
                response.set_content("OK", "text/plain");
            });

    // Fetch account key in plain text
    server.Post(
            "/account-key",
            [this](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                auto id = data["id"].get<int>();

                auto account = storage->GetByID<Account>(id);

                if (account != nullptr) {
                    auto key = account->keyHash;  // TODO need to decrypt first
                    response.set_content(key, "text/plain");
                } else {
                    response.status = 404;
                }
            }
            );
}


/**
 * Runs the main listen loop for the HTTP server.
 */
void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    server.listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
