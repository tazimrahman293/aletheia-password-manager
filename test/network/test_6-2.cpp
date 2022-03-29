////
//// Created by jeremy on 2022-03-18.
////
//
//#include "aletheia.h"
//#include "network/HTTPServer.h"
//#include "Storage.h"
//#include "data/Account.h"
//#include "data/User.h"
//
//#include "doctest.h"
//#include "httplib.h"
//#include "json.h"
//
//#include <chrono>
//#include <cstdio>
//#include <forward_list>
//#include <string>
//#include <thread>
//
//
//using json = nlohmann::json;
//
//
//int insertTestUser(Storage &storage, Authenticator &auth, int suffix)
//{
//    User user;
//    user.username = "jsmith" + std::to_string(suffix);
//    user.firstName = "John";
//    user.lastName = "Smith";
//    user.password = "password";
//    user.hash = hashToChars(auth.Encrypt("password"));
//    storage.Insert(user);
//    WARN_GT(user.pk, 0);
//    return user.pk;
//}
//
//
//int insertTestAccount(Storage &storage, int userID, int suffix)
//{
//    Account account;
//    account.label = "example";
//    account.username = "abc" + std::to_string(suffix);
//    account.url = "example.com";
//    account.keyHash = "password";
//    account.expiry = 0;
//    account.created = 0;
//    account.lastAccessed = 0;
//    account.lastModified = 0;
//    account.userID = userID;
//    storage.Insert(account);
//    WARN_GT(account.pk, 0);
//    return account.pk;
//}
//
//
//template<class T>
//T parseFromResponseBody(const std::string &body)
//{
//    using json = nlohmann::json;
//    auto data = json::parse(body);
//    data.erase("keyHash");
//    data.erase("password");
//    return data.get<T>();
//}
//
//
//void teardown(HTTPServer &srv, std::thread &thr)
//{
//    srv.Stop();
//    thr.join();
//}
//
//
//TEST_SUITE_BEGIN("api");
//
//TEST_CASE("api-create-user") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    Storage storage(dbFilename);
//    Authenticator *auth = new Authenticator();
//    srv.Init(&storage, auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    SUBCASE("valid") {
//        json j;
//        j["pk"] = -1;
//        j["username"] = "jsmith";
//        j["firstName"] = "John";
//        j["lastName"] = "Smith";
//        j["password"] = "password";
//
//        auto response = client.Post("/user", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 201);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        auto user = parseFromResponseBody<User>(response->body);
//        REQUIRE_GT(user.pk, 0);
//        REQUIRE_EQ(user.username, "jsmith");
//        REQUIRE_EQ(user.firstName, "John");
//        REQUIRE_EQ(user.lastName, "Smith");
//        REQUIRE_EQ(user.password, "");
//    }
//
//    SUBCASE("invalid") {
//        json j;
//        j["pk"] = -1;
//        j["username"] = "jsmith";
//        j["firstName"] = 1;
//        j["lastName"] = 2;
//        j["password"] = "password";
//
//        auto response = client.Post("/user", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Post("/user", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-get-user") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int numUsers = 10;
//    // Insert a test user
//    for (int i = 0; i < numUsers; i++) {
//        insertTestUser(storage, auth, i);
//    }
//
//    SUBCASE("by-pk") {
//        SUBCASE("valid") {
//            for (int i = 0; i < numUsers; i++) {
//                std::string pkArg = std::to_string(i+1);
//                auto response = client.Get(("/user?pk=" + pkArg).c_str());
//                REQUIRE_EQ(response->status, 200);
//                REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//                auto user = parseFromResponseBody<User>(response->body);
//                REQUIRE_EQ(user.pk, i+1);
//                REQUIRE_EQ(user.username, "jsmith"+std::to_string(i));
//            }
//        }
//        SUBCASE("invalid") {
//            for (int i = 0; i < 3; i++) {
//                std::string pkArg = std::to_string(9999+i);
//                auto response = client.Get(("/user?pk=" + pkArg).c_str());
//                REQUIRE_EQ(response->status, 404);
//            }
//        }
//    }
//
//    SUBCASE("by-username") {
//        SUBCASE("valid") {
//            for (int i = 0; i < numUsers; i++) {
//                std::string username = "jsmith" + std::to_string(i);
//                auto response = client.Get(("/user?username=" + username).c_str());
//                REQUIRE_EQ(response->status, 200);
//                REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//                auto user = parseFromResponseBody<User>(response->body);
//                REQUIRE_EQ(user.pk, i+1);
//                REQUIRE_EQ(user.username, username);
//            }
//        }
//        SUBCASE("invalid") {
//            for (int i = 9999; i < 9999+3; i++) {
//                std::string username = "jsmith" + std::to_string(i);
//                auto response = client.Get(("/user?username=" + username).c_str());
//                REQUIRE_EQ(response->status, 404);
//            }
//        }
//    }
//
//    SUBCASE("missing-params") {
//        auto response = client.Get("/user");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-update-user") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int id = insertTestUser(storage, auth, 1);
//    auto user = storage.GetByID<User>(id);
//
//    SUBCASE("valid") {
//        user->username = "jdoe9";
//        user->firstName = "Jane";
//        user->lastName = "Doe";
//
//        json j = *user;
//        auto response = client.Patch("/user", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 200);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        auto patchedUser = parseFromResponseBody<User>(response->body);
//        REQUIRE_EQ(patchedUser.pk, user->pk);
//        REQUIRE_EQ(patchedUser.username, user->username);
//        REQUIRE_EQ(patchedUser.firstName, user->firstName);
//        REQUIRE_EQ(patchedUser.lastName, user->lastName);
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-types") {
//            json j{
//                    {"pk", id},
//                    {"username", 1},
//                    {"firstName", true},
//                    {"lastName", false}
//            };
//            auto response = client.Patch("/user", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//        SUBCASE("bad-pk") {
//            user->pk = 9999;
//            json j = *user;
//            auto response = client.Patch("/user", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 404);
//        }
//        SUBCASE("missing-fields") {
//            auto response = client.Patch("/user", "{}", "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Patch("/user", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-delete-user") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int id = insertTestUser(storage, auth, 0);
//
//    SUBCASE("valid") {
//        json j{{"pk", id}};
//        auto response = client.Delete("/user", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 204);
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-pk") {
//            json j{{"pk", 9999}};
//            auto response = client.Delete("/user", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 204);  // 204 even if resource doesn't exist and couldn't be deleted
//        }
//        SUBCASE("bad-types") {
//            json j{{"pk", "1"}};
//            auto response = client.Delete("/user", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Delete("/user", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-list-users") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//    int numUsers;
//
//    SUBCASE("empty") { numUsers = 0; }
//    SUBCASE("single") { numUsers = 1; }
//    SUBCASE("multiple") { numUsers = 10; }
//
//    for (int i = 0; i < numUsers; i++) {
//        insertTestUser(storage, auth, i);
//    }
//
//    auto response = client.Get("/users");
//    REQUIRE_EQ(response->status, 200);
//    REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//    auto j = json::parse(response->body);
//    REQUIRE_EQ(j.size(), numUsers);
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-create-account") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int userID = insertTestUser(storage, auth, 0);
//
//    SUBCASE("valid") {
//        json j{
//                {"pk", -1},
//                {"label", "example"},
//                {"username", "abc123"},
//                {"url", "example.com"},
//                {"keyHash", "password"},
//                {"created", 0},
//                {"lastAccessed", 0},
//                {"lastModified", 0},
//                {"expiry", 0},
//                {"userID", userID}
//        };
//
//        auto response = client.Post("/account", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 201);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        json r = json::parse(response->body);
//        REQUIRE_EQ(r.at("label"), j.at("label"));
//        REQUIRE_EQ(r.at("username"), j.at("username"));
//        REQUIRE_EQ(r.at("url"), j.at("url"));
//        REQUIRE_EQ(r.at("expiry").get<long>(), j.at("expiry").get<long>());
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Post("/account", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-get-account") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int numAccounts;
//
//    int userID = insertTestUser(storage, auth, 0);
//
//    SUBCASE("valid-user") {
//        SUBCASE("empty") {
//            numAccounts = 0;
//        }
//        SUBCASE("single") {
//            numAccounts = 1;
//        }
//        SUBCASE("multiple") {
//            numAccounts = 10;
//        }
//
//        for (int i = 0; i < numAccounts; i++) {
//            insertTestAccount(storage, userID, i);
//        }
//        auto response = client.Get(("/account?user=" + std::to_string(userID)).c_str());
//        REQUIRE_EQ(response->status, 200);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        json j = json::parse(response->body);
//        REQUIRE_EQ(j.size(), numAccounts);
//    }
//
//    SUBCASE("invalid-user") {
//        SUBCASE("bad-pk") {
//            auto response = client.Get(("/account?user=" + std::to_string(9999)).c_str());
//            REQUIRE_EQ(response->status, 404);
//        }
//        SUBCASE("missing-param") {
//            auto response = client.Get("/account");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-update-account") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int userID = insertTestUser(storage, auth, 0);
//    int accountID = insertTestAccount(storage, userID, 0);
//    auto account = storage.GetByID<Account>(accountID);
//
//    SUBCASE("valid") {
//        account->username = "xyz";
//        account->label = "test";
//        account->url = "test.com";
//        account->expiry = 1;
//
//        json j = *account;
//        auto response = client.Patch("/account", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 200);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        auto patchedAccount = parseFromResponseBody<Account>(response->body);
//        REQUIRE_EQ(patchedAccount.pk, account->pk);
//        REQUIRE_EQ(patchedAccount.username, account->username);
//        REQUIRE_EQ(patchedAccount.label, account->label);
//        REQUIRE_EQ(patchedAccount.url, account->url);
//        REQUIRE_EQ(patchedAccount.expiry, account->expiry);
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-types") {
//            json j{
//                    {"pk", account->pk},
//                    {"username", 1},
//                    {"label", 3.14},
//                    {"url", true},
//                    {"expiry", "never"}
//            };
//            auto response = client.Patch("/account", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//        SUBCASE("bad-pk") {
//            account->pk = 9999;
//            json j = *account;
//            auto response = client.Patch("/account", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 404);
//        }
//        SUBCASE("missing-fields") {
//            auto response = client.Patch("/account", "{}", "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Patch("/account", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-delete-account") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int userID = insertTestUser(storage, auth, 0);
//    int accountID = insertTestAccount(storage, userID, 0);
//
//    SUBCASE("valid") {
//        json j{{"pk", accountID}};
//        auto response = client.Delete("/account", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 204);
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-pk") {
//            json j{{"pk", 9999}};
//            auto response = client.Delete("/account", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 204);  // 204 even if resource doesn't exist and couldn't be deleted
//        }
//        SUBCASE("bad-types") {
//            json j{{"pk", "1"}};
//            auto response = client.Delete("/account", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Delete("/account", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-generate-account-key") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int userID = insertTestUser(storage, auth, 0);
//    int accountID = insertTestAccount(storage, userID, 0);
//
//    SUBCASE("valid") {
//        SUBCASE("random") {
//            json j{
//                    {"pk", accountID},
//                    {"random", true},
//                    {"length", 8},
//                    {"lowers", true},
//                    {"uppers", false},
//                    {"numbers", false},
//                    {"specials", false}
//            };
//            auto response = client.Put("/account/key", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 200);
//            REQUIRE_EQ(response->body, "");
//        }
//        SUBCASE("manual") {
//            json j{
//                    {"pk", accountID},
//                    {"random", false},
//                    {"key", "hunter2"}
//            };
//            auto response = client.Put("/account/key", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 200);
//            REQUIRE_EQ(response->body, "");
//        }
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-pk") {
//            json j{
//                    {"pk", 9999},
//                    {"random", true},
//                    {"length", 8},
//                    {"lowers", true},
//                    {"uppers", false},
//                    {"numbers", false},
//                    {"specials", false}
//            };
//            auto response = client.Put("/account/key", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 404);
//        }
//        SUBCASE("bad-types") {
//            json j{
//                    {"pk", accountID},
//                    {"random", 1},
//                    {"length", 8},
//                    {"lowers", "true"},
//                    {"uppers", "false"},
//                    {"numbers", "false"},
//                    {"specials", "false"}
//            };
//            auto response = client.Put("/account/key", j.dump(), "application/json");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Put("/account/key", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-get-account-key") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int userID = insertTestUser(storage, auth, 0);
//    int accountID = insertTestAccount(storage, userID, 0);
//
//    SUBCASE("valid") {
//        auto response = client.Get(("/account/key?account=" + std::to_string(accountID)).c_str());
//        REQUIRE_EQ(response->status, 200);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        json j = json::parse(response->body);
//        int id = j.at("pk").get<int>();
//        std::string key = j.at("key").get<std::string>();
//        REQUIRE_EQ(id, accountID);
//        REQUIRE_EQ(key, "password");
//    }
//
//    SUBCASE("invalid") {
//        SUBCASE("bad-pk") {
//            auto response = client.Get(("/account/key?account=" + std::to_string(9999)).c_str());
//            REQUIRE_EQ(response->status, 404);
//        }
//        SUBCASE("missing-param") {
//            auto response = client.Get("/account/key");
//            REQUIRE_EQ(response->status, 400);
//        }
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-login") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    remove(dbFilename.c_str());
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    int id = insertTestUser(storage, auth, 0);
//    auto user = storage.GetByID<User>(id);
//    json j{{"username", user->username}, {"key", "password"}};
//
//    SUBCASE("success") {
//        auto response = client.Post("/login", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 200);
//        REQUIRE_EQ(response->get_header_value("Content-Type"), "application/json");
//
//        auto loggedInUser = parseFromResponseBody<User>(response->body);
//        REQUIRE_EQ(loggedInUser.pk, id);
//        REQUIRE_EQ(loggedInUser.username, user->username);
//    }
//
//    SUBCASE("unauthorized") {
//        j.at("key") = "hunter2";
//        auto response = client.Post("/login", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 401);
//    }
//
//    SUBCASE("no-password") {
//        j.at("key") = "";
//        auto response = client.Post("/login", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 401);
//    }
//
//    SUBCASE("bad-types") {
//        j.at("username") = 1;
//        auto response = client.Post("/login", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    SUBCASE("user-does-not-exist") {
//        j.at("username") = "i-dont-exist-9999";
//        auto response = client.Post("/login", j.dump(), "application/json");
//        REQUIRE_EQ(response->status, 401);
//    }
//
//    SUBCASE("junk") {
//        auto response = client.Post("/login", "junk", "application/json");
//        REQUIRE_EQ(response->status, 400);
//    }
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_CASE("api-logout") {
//    // SETUP
//    std::string clientConnString = "http://127.0.0.1:8089";
//    HTTPServer srv;
//    std::string dbFilename = "test/test.sqlite3";
//    Storage storage(dbFilename);
//    Authenticator auth;
//    srv.Init(&storage, &auth);
//    auto runThread = std::thread([&](){
//        srv.Run();
//    });
//    while (!srv.IsRunning()) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds{1});
//    }
//    httplib::Client client(clientConnString);
//    // END SETUP
//
//    auto response = client.Post("/logout");
//    REQUIRE_EQ(response->status, 204);
//
//    // TEARDOWN
//    srv.Stop();
//    runThread.join();
//    // END TEARDOWN
//}
//
//TEST_SUITE_END();