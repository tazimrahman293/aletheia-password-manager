//
// Created by jeremy on 2022-03-18.
//

#include "network/HTTPServer.h"
#include "Storage.h"
#include "data/User.h"

#include "doctest.h"
#include "httplib.h"
#include "json.h"

#include <chrono>
#include <cstdio>
#include <forward_list>
#include <string>
#include <thread>


using json = nlohmann::json;


std::thread setup(HTTPServer &srv)
{
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);

    auto runThread = std::thread([&](){
        srv.Run();
    });

    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }

    return runThread;
}


int insertTestUser(Storage &storage, int suffix)
{
    User user;
    user.username = "jsmith" + std::to_string(suffix);
    user.firstName = "John";
    user.lastName = "Smith";
    user.keyHash = "password";
    storage.Insert(user);
    WARN_GT(user.pk, 0);
    return user.pk;
}


template<class T>
T parseFromResponseBody(const std::string &body)
{
    using json = nlohmann::json;
    auto data = json::parse(body);
    data["keyHash"] = "";
    return data.get<T>();
}


void teardown(HTTPServer &srv, std::thread &thr)
{
    srv.Stop();
    thr.join();
}


TEST_SUITE_BEGIN("api");

TEST_CASE("api-create-user") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP

    SUBCASE("valid") {
        json j;
        j["pk"] = -1;
        j["username"] = "jsmith";
        j["firstName"] = "John";
        j["lastName"] = "Smith";
        j["keyHash"] = "password";

        auto response = client.Post("/user", j.dump(), "application/json");
        REQUIRE_EQ(response->status, 201);
        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");

        auto user = parseFromResponseBody<User>(response->body);
        REQUIRE_GT(user.pk, 0);
        REQUIRE_EQ(user.username, "jsmith");
        REQUIRE_EQ(user.firstName, "John");
        REQUIRE_EQ(user.lastName, "Smith");
        REQUIRE_EQ(user.keyHash, "");
    }

    SUBCASE("invalid") {
        json j;
        j["pk"] = -1;
        j["username"] = "jsmith";
        j["firstName"] = 1;
        j["lastName"] = 2;
        j["keyHash"] = "password";

        auto response = client.Post("/user", j.dump(), "application/json");
        REQUIRE_EQ(response->status, 400);
    }

    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-get-user") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    remove(dbFilename.c_str());
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP

    int numUsers = 10;
    // Insert a test user
    for (int i = 0; i < numUsers; i++) {
        insertTestUser(storage, i);
    }

    SUBCASE("by-pk") {
        SUBCASE("valid") {
            for (int i = 0; i < numUsers; i++) {
                std::string pkArg = std::to_string(i+1);
                auto response = client.Get(("/user?pk=" + pkArg).c_str());
                REQUIRE_EQ(response->status, 200);
                REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");

                auto user = parseFromResponseBody<User>(response->body);
                REQUIRE_EQ(user.pk, i+1);
                REQUIRE_EQ(user.username, "jsmith"+std::to_string(i));
            }
        }
        SUBCASE("invalid") {
            for (int i = 0; i < 3; i++) {
                std::string pkArg = std::to_string(9999+i);
                auto response = client.Get(("/user?pk=" + pkArg).c_str());
                REQUIRE_EQ(response->status, 404);
            }
        }
    }

    SUBCASE("by-username") {
        SUBCASE("valid") {
            for (int i = 0; i < numUsers; i++) {
                std::string username = "jsmith" + std::to_string(i);
                auto response = client.Get(("/user?username=" + username).c_str());
                REQUIRE_EQ(response->status, 200);
                REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");

                auto user = parseFromResponseBody<User>(response->body);
                REQUIRE_EQ(user.pk, i+1);
                REQUIRE_EQ(user.username, username);
            }
        }
        SUBCASE("invalid") {
            for (int i = 9999; i < 9999+3; i++) {
                std::string username = "jsmith" + std::to_string(i);
                auto response = client.Get(("/user?username=" + username).c_str());
                REQUIRE_EQ(response->status, 404);
            }
        }
    }

    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-update-user") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    remove(dbFilename.c_str());
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP

    int id = insertTestUser(storage, 1);
    auto user = storage.GetByID<User>(id);

    SUBCASE("valid") {
        user->username = "jdoe9";
        user->firstName = "Jane";
        user->lastName = "Doe";

        json j = *user;
        auto response = client.Patch("/user", j.dump(), "application/json");
        REQUIRE_EQ(response->status, 200);
        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");

        auto patchedUser = parseFromResponseBody<User>(response->body);
        REQUIRE_EQ(patchedUser.pk, user->pk);
        REQUIRE_EQ(patchedUser.username, user->username);
        REQUIRE_EQ(patchedUser.firstName, user->firstName);
        REQUIRE_EQ(patchedUser.lastName, user->lastName);
    }

    SUBCASE("invalid") {
        SUBCASE("bad-types") {
            json j{
                    {"pk", id},
                    {"username", 1},
                    {"firstName", true},
                    {"lastName", false}
            };
            auto response = client.Patch("/user", j.dump(), "application/json");
            REQUIRE_EQ(response->status, 400);
        }
        SUBCASE("bad-pk") {
            user->pk = 9999;
            json j = *user;
            auto response = client.Patch("/user", j.dump(), "application/json");
            REQUIRE_EQ(response->status, 404);
        }
    }

    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-delete-user") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-list-users") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-create-account") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-get-account") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-update-account") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-delete-account") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-generate-account-key") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-get-account-key") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-login") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-logout") {
    // SETUP
    std::string clientConnString = "http://127.0.0.1:8089";
    HTTPServer srv;
    std::string dbFilename = "test/test.sqlite3";
    Storage storage(dbFilename);
    srv.Init(&storage);
    auto runThread = std::thread([&](){
        srv.Run();
    });
    while (!srv.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }
    httplib::Client client(clientConnString);
    // END SETUP


    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_SUITE_END();