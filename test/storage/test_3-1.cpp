//
// Created by jeremy on 2022-03-10.
//

#include "data/Account.h"
#include "data/User.h"
#include "Storage.h"

#include "doctest.h"

#include <cstdio>
#include <memory>


TEST_SUITE_BEGIN("storage");

TEST_CASE("constructor") {

    // Remove the existing db to get a fresh start
    remove("test/test.sqlite3");

    SUBCASE("memory database") {
        Storage storage(":memory:");
        REQUIRE_NE(&storage, nullptr);
    }

    SUBCASE("file database") {
        Storage storage("test/test.sqlite3");
        REQUIRE_NE(&storage, nullptr);
    }

}

TEST_CASE("insert") {

    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");

    SUBCASE("users") {
        User user;
        user.firstName = "First";
        user.lastName = "Last";
        user.keyHash = "pass";
        CHECK_EQ(user.pk, -1);

        storage.Insert(user);
        REQUIRE_EQ(user.pk, 1);
    }

    SUBCASE("accounts") {
        User user;
        storage.Insert(user);
        CHECK_EQ(user.pk, 1);

        Account account;
        account.label = "steam";
        account.username = "johnsmith101";
        account.keyHash = "password";
        account.url = "steampowered.com";
        CHECK_EQ(account.pk, -1);
        CHECK_EQ(account.userID, -1);

        account.userID = 1;
        storage.Insert(account);
        REQUIRE_EQ(account.pk, 1);
    }
}

TEST_CASE("update") {

}

TEST_CASE("insert or update") {

}

TEST_CASE("get by ID") {

}

TEST_CASE("remove") {

}

TEST_CASE("get all users") {

}

TEST_CASE("get all accounts by user ID") {

}

TEST_SUITE_END();