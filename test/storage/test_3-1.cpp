//
// Created by jeremy on 2022-03-10.
//

#include "data/Account.h"
#include "data/User.h"
#include "Storage.h"

#include "doctest.h"

#include <cstdio>
#include <iostream>
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

TEST_CASE("storage constructor") {

    // Remove the existing db to get a fresh start
    remove(dbFilename.c_str());

    SUBCASE("construct memory database") {
        Storage storage(":memory:");
        REQUIRE_NE(&storage, nullptr);
    }

    SUBCASE("construct file database") {
        Storage storage(dbFilename);
        REQUIRE_NE(&storage, nullptr);
    }

}

TEST_CASE("storage insert") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("insert users") {
        User user = createTestUser();
        CHECK_EQ(user.pk, -1);

        storage.Insert(user);
        REQUIRE_GT(user.pk, 0);
    }

    SUBCASE("insert accounts") {
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

TEST_CASE("storage get by ID") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("get users by id") {
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

    SUBCASE("get accounts by id") {
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

TEST_CASE("storage update") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("update users") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        user.firstName = "Changed";
        storage.Update(user);

        auto record = storage.GetByID<User>(user.pk);
        CHECK_EQ(record->pk, user.pk);
        REQUIRE_EQ(record->firstName, user.firstName);
    }

    SUBCASE("update accounts") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        Account account = createTestAccount();
        account.userID = user.pk;
        storage.Insert(account);
        WARN_GT(account.pk, 0);

        account.username = "changed";
        storage.Update(account);

        auto record = storage.GetByID<Account>(account.pk);
        CHECK_EQ(record->pk, account.pk);
        REQUIRE_EQ(record->username, account.username);
    }
}

TEST_CASE("storage remove") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);

    SUBCASE("remove users") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        storage.Remove<User>(user.pk);

        auto record = storage.GetByID<User>(user.pk);
        REQUIRE_EQ(record, nullptr);
    }

    SUBCASE("remove accounts") {
        User user = createTestUser();
        storage.Insert(user);
        WARN_GT(user.pk, 0);

        Account account = createTestAccount();
        account.userID = user.pk;
        storage.Insert(account);
        WARN_GT(account.pk, 0);

        storage.Remove<Account>(account.pk);

        auto record = storage.GetByID<Account>(account.pk);
        REQUIRE_EQ(record, nullptr);
    }
}

TEST_CASE("storage get all users") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);
    int maxUsers;

    SUBCASE("1 user") { maxUsers = 1; }
    SUBCASE("10 users") { maxUsers = 10; }
    SUBCASE("100 users") { maxUsers = 100; }

    for (int i = 0; i < maxUsers; i++) {
        User user = createTestUser();
        user.firstName += std::to_string(i);
        storage.Insert(user);
        WARN_GT(user.pk, 0);
    }
    auto allUsers = storage.GetAllUsers();
    REQUIRE_EQ(allUsers.size(), maxUsers);

    for (auto& user : allUsers) {
        REQUIRE_GT(user.pk, 0);
    }
}

TEST_CASE("storage get all accounts by user ID") {

    remove(dbFilename.c_str());
    Storage storage(dbFilename);
    int maxAccounts;

    SUBCASE("1 account") { maxAccounts = 1; }
    SUBCASE("10 accounts") { maxAccounts = 10; }
    SUBCASE("100 accounts") { maxAccounts = 100; }

    User user = createTestUser();
    storage.Insert(user);
    WARN_GT(user.pk, 0);

    for (int i = 0; i < maxAccounts; i++) {
        Account account = createTestAccount();
        account.username += std::to_string(i);
        account.userID = user.pk;
        storage.Insert(account);
        WARN_GT(account.pk, 0);
    }
    auto allAccounts = storage.GetAllAccountsByUserID(user.pk);
    REQUIRE_EQ(allAccounts.size(), maxAccounts);

    for (auto& account : allAccounts) {
        REQUIRE_GT(account.pk, 0);
    }
}

TEST_SUITE_END();