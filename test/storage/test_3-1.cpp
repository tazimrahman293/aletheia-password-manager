//
// Created by jeremy on 2022-03-10.
//

#include "data/Account.h"
#include "data/User.h"
#include "Storage.h"

#include "doctest.h"

#include <cstdio>
#include <memory>
#include <string>


User createTestUser() {
    User user;
    user.firstName = "First";
    user.lastName = "Last";
    user.keyHash = "pass";
    return user;
}


Account createTestAccount() {
    Account account;
    account.label = "steam";
    account.username = "johnsmith101";
    account.keyHash = "password";
    account.url = "steampowered.com";
    return account;
}


TEST_SUITE_BEGIN("storage");

const std::string dbFilename = "test/test.sqlite3";

TEST_CASE("constructor") {

    // Remove the existing db to get a fresh start
    remove(dbFilename.c_str());

    SUBCASE("memory database") {
        Storage storage(":memory:");
        REQUIRE_NE(&storage, nullptr);
    }

    SUBCASE("file database") {
        Storage storage(dbFilename);
        REQUIRE_NE(&storage, nullptr);
    }

}

TEST_CASE("insert") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("users") {
        User user = createTestUser();
        CHECK_EQ(user.pk, -1);

        storage.Insert(user);
        REQUIRE_GT(user.pk, 0);
    }

    SUBCASE("accounts") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        Account account = createTestAccount();
        CHECK_EQ(account.pk, -1);
        CHECK_EQ(account.userID, -1);

        account.userID = user.pk;
        storage.Insert(account);
        REQUIRE_GT(account.pk, 0);
    }
}

TEST_CASE("get by ID") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("users") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        auto record = storage.GetByID<User>(user.pk);
        REQUIRE_EQ(record->pk, user.pk);
        REQUIRE_EQ(record->firstName, user.firstName);
        REQUIRE_EQ(record->lastName, user.lastName);
        REQUIRE_EQ(record->keyHash, user.keyHash);
        REQUIRE_EQ(record->typeID, user.typeID);
    }

    SUBCASE("accounts") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        Account account = createTestAccount();
        account.userID = user.pk;
        storage.Insert(account);
        WARN_GT(account.pk, 0);

        auto record = storage.GetByID<Account>(account.pk);
        REQUIRE_EQ(record->pk, account.pk);
        REQUIRE_EQ(record->label, account.label);
        REQUIRE_EQ(record->username, account.username);
        REQUIRE_EQ(record->keyHash, account.keyHash);
        REQUIRE_EQ(record->url, account.url);
        REQUIRE_EQ(record->created, account.created);
        REQUIRE_EQ(record->lastAccessed, account.lastAccessed);
        REQUIRE_EQ(record->lastModified, account.lastModified);
        REQUIRE_EQ(record->expiry, account.expiry);
        REQUIRE_EQ(record->userID, account.userID);
    }
}

TEST_CASE("update") {

remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("users") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        user.firstName = "Changed";
        storage.Update(user);

        auto record = storage.GetByID<User>(user.pk);
        CHECK_EQ(record->pk, user.pk);
        REQUIRE_EQ(record->firstName, user.firstName);
    }

    SUBCASE("accounts") {
        User user = createTestUser();
        storage.Insert(user);
        CHECK_GT(user.pk, 0);

        Account account = createTestAccount();
        account.userID = user.pk;
        storage.Insert(account);
        CHECK_GT(account.pk, 0);

        account.username = "changed";
        storage.Update(account);

        auto record = storage.GetByID<Account>(account.pk);
        CHECK_EQ(record->pk, account.pk);
        REQUIRE_EQ(record->username, account.username);
    }
}

TEST_CASE("insert or update") {

}

TEST_CASE("remove") {

}

TEST_CASE("get all users") {

}

TEST_CASE("get all accounts by user ID") {

}

TEST_SUITE_END();