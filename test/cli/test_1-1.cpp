//
// Created by Tazim Rahman on 2022-03-26.
//


#include "doctest.h"

#include "cli/CommandLine.h"

TEST_SUITE_BEGIN("cli");

TEST_CASE("cli-constructor") {
    Commandline cli = new Commandline();
}

TEST_SUITE_END();