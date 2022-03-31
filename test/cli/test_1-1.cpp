//
// Created by Tazim Rahman on 2022-03-26.
//


#include "doctest.h"

#include "aletheia.h"
#include "auth/Authenticator.h"
#include "cli/CommandLine.h"
#include "cli/InputParser.h"
#include "data/User.h"
#include "Storage.h"

#include <cstdio>
#include <iostream>
#include <string>


TEST_SUITE_BEGIN("cli");

TEST_CASE("cli-parser") {
    int argc;

    SUBCASE("no-args") {
        argc = 1;
        char *argv[] = { "exe-name" };
        InputParser parser(argc, argv);

        CHECK_EQ(parser.CountTokens(), argc-1);
        CHECK_NOTHROW(parser.GetTokenAtPosition(1));
    }

    SUBCASE("option-flags") {
        argc = 5;
        char *argv[] = { "exe-name", "-a", "aval", "-b", "bval" };
        InputParser parser(argc, argv);

        CHECK_EQ(parser.CountTokens(), argc-1);

        CHECK(parser.InputExists("-a"));
        CHECK(parser.InputExists("-b"));
        CHECK(parser.InputExists("aval"));
        CHECK(parser.InputExists("bval"));

        CHECK(parser.IsTokenAtPosition("-a", 0));
        CHECK(parser.IsTokenAtPosition("aval", 1));
        CHECK(parser.IsTokenAtPosition("-b", 2));
        CHECK(parser.IsTokenAtPosition("bval", 3));

        CHECK_FALSE(parser.IsTokenAtPosition("-a", 1));

        CHECK_EQ(parser.GetTokenAtPosition(0), "-a");
        CHECK_NE(parser.GetTokenAtPosition(1), "-a");

        CHECK_EQ(parser.GetOption("-a"), "aval");
        CHECK_EQ(parser.GetOption("-b"), "bval");

        CHECK_EQ(parser.GetOption("-c"), "");
    }
}

TEST_CASE("cli-constructor") {
    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr);
    REQUIRE_NE(cli, nullptr);
    // TODO Put in subcases for different command line options
}

TEST_CASE("cli-quit") {
    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);

    REQUIRE(cli->IsRunning());

    cli->inStream.str("quit\n");
    std::string command = cli->GetInput("");
    REQUIRE_EQ(command, "quit");
    cli->HandleCommands(command);
    REQUIRE_FALSE(cli->IsRunning());
}

TEST_CASE("cli-register") {
    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage *storage = new Storage("test/test.sqlite3");
    Authenticator *auth = new Authenticator();
    cli->Init(storage, auth);

    REQUIRE(cli->IsRunning());

    SUBCASE("valid") {
        cli->inStream.str("jsmith1\nJohn\nSmith\npassword1\npassword1\n");
        cli->HandleCommands("register");
        CHECK_FALSE(cli->outStream.str().empty());

        auto user = storage->GetUserByUsername("jsmith1");
        REQUIRE_NE(user, nullptr);
        CHECK_EQ(user->firstName, "John");
        CHECK_EQ(user->lastName, "Smith");
    }

    SUBCASE("password-mismatch") {
        cli->inStream.str("jsmith1\nJohn\nSmith\npassword1\npassword2\n");
        cli->HandleCommands("register");
        CHECK_FALSE(cli->outStream.str().empty());

        CHECK_NE(cli->outStream.str().find("match"), std::string::npos);
    }

    SUBCASE("username-taken") {
        User user;
        user.username = "jsmith1";
        user.password = "password";
        storage->Insert(user);
        auto users = storage->GetAllUsers();
        CHECK_EQ(users.size(), 1);

        cli->inStream.str("jsmith1\nJohn\nSmith\npassword1\npassword2\n");
        cli->HandleCommands("register");
        CHECK_FALSE(cli->outStream.str().empty());
        CHECK_NE(cli->outStream.str().find("exists"), std::string::npos);
    }

}

TEST_CASE("cli-login") {
    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");
    Authenticator auth;
    cli->Init(&storage, &auth);

    REQUIRE(cli->IsRunning());

    SUBCASE("valid") {
        cli->DoRegister("jsmith1", "John", "Smith", "password1");
        cli->DoLogout();

        cli->inStream.str("jsmith1\npassword1\n");
        cli->HandleCommands("login");
        CHECK_FALSE(cli->outStream.str().empty());

        CHECK(cli->IsLoggedIn());
    }

    SUBCASE("invalid-password") {
        cli->DoRegister("jsmith1", "John", "Smith", "password1");
        cli->DoLogout();

        cli->inStream.str("jsmith1\npassword2\n");
        cli->HandleCommands("login");
        CHECK_FALSE(cli->outStream.str().empty());

        CHECK_FALSE(cli->IsLoggedIn());
    }

}

TEST_CASE("cli-new-account") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");
    Authenticator auth;
    cli->Init(&storage, &auth);

    REQUIRE(cli->IsRunning());

    SUBCASE("valid") {
        cli->DoRegister("jsmith1", "John", "Smith", "password1");
        CHECK(cli->IsLoggedIn());

        cli->inStream.str("a-label\na-username\na-password\na-url\n");
        cli->HandleCommands("new-account");
        CHECK_FALSE(cli->outStream.str().empty());

        auto user = storage.GetUserByUsername("jsmith1");
        REQUIRE_GT(user->pk, 0);
        auto account = storage.GetAllAccountsByUserID(user->pk)[0];
        CHECK_GT(account.pk, 0);
        CHECK_EQ(account.label, "a-label");
        CHECK_EQ(account.username, "a-username");
        CHECK_EQ(auth.Decrypt(charsToHash(account.hash)), "a-password");
        CHECK_EQ(account.url, "a-url");
    }

    SUBCASE("not-signed-in") {
        cli->DoRegister("jsmith1", "John", "Smith", "password1");
        cli->DoLogout();

        cli->inStream.str("a-label\na-username\na-password\na-url\n");
        cli->HandleCommands("new-account");
        CHECK_FALSE(cli->outStream.str().empty());
        CHECK_NE(cli->outStream.str().find("Please sign in"), std::string::npos);

        auto user = storage.GetUserByUsername("jsmith1");
        REQUIRE_GT(user->pk, 0);
        auto accounts = storage.GetAllAccountsByUserID(user->pk);
        CHECK_EQ(accounts.size(), 0);
    }

}

TEST_CASE("cli-edit-account") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");
    Authenticator auth;
    cli->Init(&storage, &auth);

    REQUIRE(cli->IsRunning());

    cli->DoRegister("jsmith1", "John", "Smith", "password1");
    CHECK(cli->IsLoggedIn());

    cli->inStream.str("a-label\na-username\na-password\na-url\n");
    cli->HandleCommands("new-account");
    CHECK_FALSE(cli->outStream.str().empty());

    SUBCASE("valid") {
        SUBCASE("edit-label") {
            cli->inStream.str("a-label\nlabel\nb-label\n");
            cli->HandleCommands("edit-account");
            CHECK_FALSE(cli->outStream.str().empty());
            auto account = storage.GetByID<Account>(1);
            CHECK_EQ(account->label, "b-label");
        }
        SUBCASE("edit-username") {
            cli->inStream.str("a-label\nusername\nb-username\n");
            cli->HandleCommands("edit-account");
            CHECK_FALSE(cli->outStream.str().empty());
            auto account = storage.GetByID<Account>(1);
            CHECK_EQ(account->username, "b-username");
        }
        SUBCASE("edit-password") {
            cli->inStream.str("a-label\npassword\nb-password\nb-password\n");
            cli->HandleCommands("edit-account");
            CHECK_FALSE(cli->outStream.str().empty());
            auto account = storage.GetByID<Account>(1);
            CHECK_EQ(auth.Decrypt(charsToHash(account->hash)), "b-password");
        }
        SUBCASE("edit-url") {
            cli->inStream.str("a-label\nurl\nb-url\n");
            cli->HandleCommands("edit-account");
            CHECK_FALSE(cli->outStream.str().empty());
            auto account = storage.GetByID<Account>(1);
            CHECK_EQ(account->url, "b-url");
        }
        SUBCASE("edit-expiry") {
            cli->inStream.str("a-label\nexpiry\n");
            cli->HandleCommands("edit-account");
            CHECK_FALSE(cli->outStream.str().empty());
            CHECK_NE(cli->outStream.str().find("NOT IMPLEMENTED"), std::string::npos);
        }
    }

    SUBCASE("invalid-field") {
        cli->inStream.str("a-label\nnonsense-field\n");
        cli->HandleCommands("edit-account");
        CHECK_FALSE(cli->outStream.str().empty());
        CHECK_NE(cli->outStream.str().find("Invalid field"), std::string::npos);
    }

    SUBCASE("account-not-found") {
        cli->inStream.str("b-label\n");
        cli->HandleCommands("edit-account");
        CHECK_FALSE(cli->outStream.str().empty());
        CHECK_NE(cli->outStream.str().find("not found"), std::string::npos);
    }

}

TEST_CASE("cli-view-accounts") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");
    Authenticator auth;
    cli->Init(&storage, &auth);

    REQUIRE(cli->IsRunning());

    cli->DoRegister("jsmith1", "John", "Smith", "password1");
    CHECK(cli->IsLoggedIn());

    cli->HandleCommands("view-accounts");
    CHECK_NE(cli->outStream.str().find("No accounts"), std::string::npos);

    for (int i = 0; i < 10; i++) {
        cli->inStream.str("label"+std::to_string(i)+"\na-username\na-password\na-url\n");
        cli->HandleCommands("new-account");
        CHECK_FALSE(cli->outStream.str().empty());
    }

    cli->HandleCommands("view-accounts");
    for (int i = 0; i < 10; i++) {
        CHECK_NE(cli->outStream.str().find("label"+std::to_string(i)), std::string::npos);
    }

}

TEST_CASE("cli-new-password") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    Storage storage("test/test.sqlite3");
    Authenticator auth;
    cli->Init(&storage, &auth);
    int passwordLength;
    std::string baseOutput = "New Password Generated: \n";
    baseOutput += "How long would you like the password to be?\n";

    REQUIRE(cli->IsRunning());

    SUBCASE("length-1") { passwordLength = 1; }
    SUBCASE("length-10") { passwordLength = 10; }
    SUBCASE("length-100") { passwordLength = 100; }

    cli->inStream.str(std::to_string(passwordLength)+"\n");
    cli->HandleCommands("new-password");
    CHECK_FALSE(cli->outStream.str().empty());
    CHECK_EQ(cli->outStream.str().size(), baseOutput.size()+passwordLength+1);
}

TEST_CASE("cli-help") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, true);
    remove("test/test.sqlite3");
    cli->HandleCommands("help");
    CHECK_NE(cli->outStream.str().find("Command list for Aletheia"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("login"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("register"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("new-account"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("view-accounts"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("edit-account"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("new-password"), std::string::npos);
    CHECK_NE(cli->outStream.str().find("quit"), std::string::npos);

}

TEST_CASE("non-test-mode") {

    int argc = 1;
    char *argv[] = { "exe-name" };
    CommandLine *cli = new CommandLine(argc, argv, nullptr, false);
    cli->HandleCommands("invalid!");
}

TEST_SUITE_END();
