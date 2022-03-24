//
// Created by jeremy on 2022-03-14.
//

#include "network/HTTPServer.h"
#include "Storage.h"

#include "doctest.h"
#include "httplib.h"

#include <chrono>
#include <forward_list>
#include <string>
#include <thread>


std::string clientConnString = "http://127.0.0.1:8089";
std::string dbFilename = "test/test.sqlite3";

TEST_SUITE_BEGIN("network");

TEST_CASE("network-constructor") {

    SUBCASE("network-constructor-default") {
        HTTPServer server;
        REQUIRE_NE(&server, nullptr);
    }

    SUBCASE("network-constructor-port-only") {
        for (int i = 1024; i < 49151; i += 1000) {
            HTTPServer server(i);
            REQUIRE_NE(&server, nullptr);
        }
    }

    SUBCASE("network-constructor-port-address") {
        std::forward_list<std::string> hosts = {
                "0.0.0.0",
                "127.0.0.1",
                "8.8.8.8",
                "192.168.1.12"
        };
        for (auto &host : hosts) {
            HTTPServer server(host, 8089);
            REQUIRE_NE(&server, nullptr);
        }
    }
}

TEST_CASE("network-init") {

    HTTPServer server;
    Storage storage(dbFilename);
    REQUIRE_NOTHROW(server.Init(&storage));

}

TEST_CASE("network-connect") {

    HTTPServer server;
    Storage storage(dbFilename);
    server.Init(&storage);

    auto runThread = std::thread([&](){
        server.Run();
    });

    while (!server.IsRunning()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
    }

    httplib::Client client(clientConnString);

    auto response = client.Get("/hello");
    REQUIRE_EQ(response->status, 200);
    REQUIRE_EQ(response->get_header_value("Content-Type"), "text/plain");
    REQUIRE_EQ(response->body, "Hello, world!");

    server.Stop();
    runThread.join();
}

TEST_SUITE_END();  // network