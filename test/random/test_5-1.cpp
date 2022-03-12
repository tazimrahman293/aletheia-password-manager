// test_5-1.cpp
// Contains the function definitions for testing User Story 5-1.
// Authors: Tyrel Kostyk

#include "random/RandomNumberGenerator.h"

#include "doctest.h"


TEST_SUITE_BEGIN("random");

TEST_CASE("constructor") {
    RandomNumberGenerator *rng = nullptr;
    CHECK_EQ(rng, nullptr);

    rng = new RandomNumberGenerator();
    REQUIRE_NE(rng, nullptr);
}

TEST_CASE("bounds") {
    RandomNumberGenerator *rng = new RandomNumberGenerator();
    int minBound, maxBound;
    int newValue;

    SUBCASE("0-10") {
        minBound = 0; maxBound = 10;
    }

    SUBCASE("1-1") {
        minBound = maxBound = 1;
    }

    SUBCASE("-10-0") {
        minBound = -10; maxBound = 0;
    }

    SUBCASE("10-0") {
        minBound = 10; maxBound = 0;
    }

    for (int i = 0; i < 2 * (maxBound - minBound + 1); i++) {
        newValue = rng->GetNew(minBound, maxBound);
        CHECK_GE(newValue, minBound);
        CHECK_LE(newValue, maxBound);
    }
}

TEST_SUITE_END();
