//
// Created by jeremy on 2022-03-14.
//

#include "network/HTTPServer.h"
#include "Storage.h"

#include "doctest.h"

#include <forward_list>
#include <string>

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
    Storage storage("test/test.sqlite3");
    REQUIRE_NOTHROW(server.Init(&storage));

}

TEST_SUITE_END();  // network