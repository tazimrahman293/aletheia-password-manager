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

// #include "events/LoginAttemptEvent.h"
// #include "events/LogoutEvent.h"
// #include "events/AccountCreateEvent.h"
// #include "events/AccountUpdateEvent.h"
// #include "events/AccountDeleteEvent.h"


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
    assert(store != nullptr && "Storage cannot be nullptr!");

    this->storage = store;

    using httplib::Request, httplib::Response;
    using json = nlohmann::json;

    // For testing purposes
    Get(
            "/hello",
            [](const Request& request, Response& response) -> void
            {
                response.set_content("Hello, world!", "text/plain");
            });

    // User login attempt
    Post(
            "/login",
            [this](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                int id;
                std::string pass;
                try {
                    id = data.at("pk").get<int>();
                    pass = data.at("key").get<std::string>();
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                auto user = storage->GetByID<User>(id);

                if (user != nullptr) {
                    // TODO hash password/key to check if valid login
                    if (pass.empty()) {  // TODO or other problems with the formation of the password, or if invalid
                        response.status = 401;
                        return;
                    }
                    if (pass == user->keyHash) {
                        // TODO obviously we need to hash the sent password and compare with the keyHash
                        // TODO create a new session (token in a cookie maybe)
                    }
                } else {
                    response.status = 401;
                }

                response.status = 204;
            });

    // User logout
    Post(
            "/logout",
            [this](const Request& request, Response& response) -> void
            {
                // TODO end the session
                response.status = 204;
            });

    // Create a new user profile
    Post(
            "/user",
            [this](const Request& request, Response& response) -> void
            {
                User record;
                try {
                    record = parseRecordFromJSON<User>(request.body);
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                storage->Insert(record);

                if (record.pk > 0) {
                    json j = {{"pk", record.pk}};

                    response.status = 201;
                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 500;
                    response.set_content("Unable to store new User record.", "text/plain");
                }
            });

    // List all users in the current database
    Get(
            "/user",
            [this](const Request& request, Response& response) -> void
            {
                auto users = storage->GetAllUsers();
                json j = json::array();
                for (auto& user : users) {
                    j.emplace_back(user);
                    j.back().erase("keyHash");  // Don't transmit key on this endpoint
                }

                response.set_content(j.dump(), "application/json");
            });

    // Update a user profile
    Patch(
            "/user",
            [this](const Request& request, Response& response) -> void
            {
                json data;
                try {
                    data = json::parse(request.body);
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                std::unique_ptr<User> user;
                try {
                    user = storage->GetByID<User>(data.at("pk").get<int>());
                } catch (const json::exception& err) {
                    response.status = 400;
                }

                if (user != nullptr) {
                    // Perform the update

                    if (data.contains("username"))
                        user->username = data.at("username").get<std::string>();

                    if (data.contains("firstName"))
                        user->firstName = data.at("firstName").get<std::string>();

                    if (data.contains("lastName"))
                        user->lastName = data.at("lastName").get<std::string>();

                    storage->Update(*user);

                } else {
                    response.status = 404;
                    return;
                }

                response.status = 204;

            });

    // Remove user
    Delete(
            "/user",
            [this](const Request& request, Response& response) -> void
            {
                json data = json::parse(request.body);
                int id;
                try {
                    id = data.at("pk").get<int>();
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                storage->Remove<User>(id);

                response.status = 204;
            });

    // Create new account
    Post(
            "/account",
            [this](const Request& request, Response& response) -> void
            {
                Account record;
                try {
                    record = parseRecordFromJSON<Account>(request.body);
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                storage->Insert(record);

                if (record.pk > 0) {
                    json j;
                    j["pk"] = record.pk;
                    j["created"] = record.created;
                    j["lastAccessed"] = record.lastAccessed;
                    j["lastModified"] = record.lastModified;

                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 500;
                    response.set_content("Unable to store new Account record.", "text/plain");
                }
            });

    // Get all accounts for a particular user
    Get(
            "/account",
            [this](const Request& request, Response& response) -> void
            {
                int id;
                if (request.has_param("user")) {
                    id = std::stoi(request.get_param_value("user"));
                } else {
                    response.status = 400;
                    return;
                }

                // First check that the user exists
                auto user = storage->GetByID<User>(id);
                if (user == nullptr) {
                    response.status = 404;
                    return;
                }

                auto accounts = storage->GetAllAccountsByUserID(id);

                json j = json::array();
                for (auto& account : accounts) {
                    j.emplace_back(account);
                    j.back().erase("keyHash");  // Don't transmit key on this endpoint
                }

                response.set_content(j.dump(), "application/json");
            });

    // Edit existing account
    Patch(
            "/account",
            [this](const Request& request, Response& response) -> void
            {
                json data;
                try {
                    data = json::parse(request.body);
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                std::unique_ptr<Account> account;
                try {
                    account = storage->GetByID<Account>(data.at("pk").get<int>());
                } catch (json::exception& err) {
                    response.status = 400;
                    return;
                }

                if (account != nullptr) {
                    // Perform the update

                    if (data.contains("label"))
                        account->label = data.at("label").get<std::string>();

                    if (data.contains("username"))
                        account->username = data.at("username").get<std::string>();

                    if (data.contains("url"))
                        account->url = data.at("url").get<std::string>();

                    if (data.contains("expiry"))
                        account->expiry = data.at("expiry").get<long>();

                    // TODO update lastModified (now)

                    storage->Update(*account);

                } else {
                    // Account with primary key given in request was not found
                    response.status = 404;
                    return;
                }

            });

    // Remove account
    Delete(
            "/account",
            [this](const Request& request, Response& response) -> void
            {
                json data = json::parse(request.body);
                int id;
                try {
                    id = data.at("pk").get<int>();
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                storage->Remove<Account>(id);

                response.status = 204;
            });

    // Fetch account key in plain text
    Get(
            "/account/key",
            [this](const Request& request, Response& response) -> void
            {
                int id;
                if (request.has_param("account")) {
                    id = std::stoi(request.get_param_value("account"));
                } else {
                    response.status = 400;
                    return;
                }

                auto account = storage->GetByID<Account>(id);

                if (account != nullptr) {
                    json j;
                    j["pk"] = account->pk;
                    j["key"] = account->keyHash;  // TODO need to decrypt first
                    response.set_content(j.dump(), "application/json");
                } else {
                    response.status = 404;
                }
            }
            );

    // Update account key
    Put(
            "/account/key",
            [this](const Request& request, Response& response) -> void
            {
                auto data = json::parse(request.body);
                int id;
                std::string key;
                try {
                    id = data.at("pk").get<int>();
                    key = data.at("key").get<std::string>();
                } catch (const json::exception& err) {
                    response.status = 400;
                    return;
                }

                auto account = storage->GetByID<Account>(id);

                if (account != nullptr) {
                    account->keyHash = key;
                    storage->Update(*account);
                } else {
                    response.status = 404;
                }

                response.status = 204;
            }
            );
}


/**
 * Runs the main listen loop for the HTTP server.
 */
void HTTPServer::Run()
{
    std::cout << "HTTP server listening at " << hostAddress << " on port " << hostPort << "..." << std::endl;
    listen(hostAddress.c_str(), hostPort, SOCK_STREAM);
}
