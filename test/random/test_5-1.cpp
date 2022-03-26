// test_5-1.cpp
// Contains the function definitions for testing User Story 5-1.
// Authors: Tyrel Kostyk

#include "random/RandomNumberGenerator.h"

#include "doctest.h"


TEST_SUITE_BEGIN("random");

TEST_CASE("random-constructor") {
    RandomNumberGenerator *rng = nullptr;
    CHECK_EQ(rng, nullptr);

    rng = new RandomNumberGenerator();
    REQUIRE_NE(rng, nullptr);
}

TEST_CASE("random-bounds") {
    RandomNumberGenerator *rng = new RandomNumberGenerator();
    int minBound = 0, maxBound = 0;
    int newValue = 0, oldValue = 0;
	int matchCounter = 0, matchMax = 0;

	SUBCASE("random-valid-bounds") {
		SUBCASE("random-valid-bounds-0-10") {
	        minBound = 0; maxBound = 10;
	    }

	    SUBCASE("random-valid-bounds-1-1") {
	        minBound = maxBound = 1;
	    }

		SUBCASE("random-valid-bounds-1-1") {
	        minBound = 22;
			maxBound = 99;
	    }

		// run through entire range twice
		int testCount = 2 * (maxBound - minBound);
		// don't allow more than half of the range to be duplicates
		oldValue = 0;
		matchCounter = 0;
		matchMax = testCount / 2;
		for (int i = 0; i < testCount; i++) {
			// get new value
			newValue = rng->GetNew(minBound, maxBound);
			// check new value is above (or equal to) minimum bound
			CHECK_GE(newValue, minBound);
			// check new value is below (or equal to) maximum bound
			CHECK_LE(newValue, maxBound);
			// increment counter if a match is detected
			if (oldValue == newValue)
				matchCounter++;
			// check that too many matches have not occured
			CHECK_LE(matchCounter, matchMax);
			// store new value
			oldValue = newValue;
		}
	}

	SUBCASE("random-invalid-bounds") {
		SUBCASE("random-invalid-bounds-n10-0") {
	        minBound = -10; maxBound = 0;
	    }

	    SUBCASE("random-invalid-bounds-10-0") {
	        minBound = 10; maxBound = 0;
	    }

		SUBCASE("random-invalid-bounds-1-0") {
			minBound = 1; maxBound = 0;
		}

		SUBCASE("random-invalid-bounds-n1-100") {
			minBound = -1; maxBound = 100;
		}

		SUBCASE("random-invalid-bounds-100-99") {
			minBound = 100; maxBound = 99;
		}

		// get new value
		newValue = rng->GetNew(minBound, maxBound);

		// confirm that error value (0) is returned
		CHECK_EQ(newValue, 0);
	}
}

TEST_SUITE_END();
