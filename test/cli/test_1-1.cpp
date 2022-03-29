//
// Created by Tazim Rahman on 2022-03-26.
//


#include "doctest.h"

#include "cli/CommandLine.h"

#include <iostream>


TEST_SUITE_BEGIN("cli");

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

TEST_SUITE_END();
