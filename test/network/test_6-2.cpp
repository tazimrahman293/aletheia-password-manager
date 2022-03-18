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
    }

    SUBCASE("invalid") {
        json j;
        j["pk"] = -1;
        j["username"] = "jsmith";
        j["firstName"] = 1;
        j["lastName"] = 2;
        j["keyHash"] = "password";
    }

    // TEARDOWN
    srv.Stop();
    runThread.join();
    // END TEARDOWN
}

TEST_CASE("api-get-user") {

}

TEST_CASE("api-update-user") {

}

TEST_CASE("api-delete-user") {

}

TEST_CASE("api-list-users") {

}

TEST_CASE("api-create-account") {

}

TEST_CASE("api-get-account") {

}

TEST_CASE("api-update-account") {

}

TEST_CASE("api-delete-account") {

}

TEST_CASE("api-generate-account-key") {

}

TEST_CASE("api-get-account-key") {

}

TEST_CASE("api-login") {

}

TEST_CASE("api-logout") {

}

TEST_SUITE_END();