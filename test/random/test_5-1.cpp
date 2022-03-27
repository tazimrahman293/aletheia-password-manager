// test_5-1.cpp
// Contains the function definitions for testing User Story 5-1.
// Authors: Tyrel Kostyk

#include "random/RandomNumberGenerator.h"
#include "random/PasswordGenerator.h"

#include "doctest.h"

// un-comment the line below to enable testing for randomness. Makes tests very slow.
// #define TEST_RANDOMNESS	(1)


TEST_SUITE_BEGIN("rng");

TEST_CASE("rng-constructor") {
    RandomNumberGenerator *rng = nullptr;
    CHECK_EQ(rng, nullptr);

    rng = new RandomNumberGenerator();
    REQUIRE_NE(rng, nullptr);
}

TEST_CASE("rng-bounds") {
    RandomNumberGenerator *rng = new RandomNumberGenerator();
    int minBound = 0, maxBound = 0;
    int newValue = 0, oldValue = 0;
	int matchCounter = 0, matchMax = 0;

	SUBCASE("rng-valid-bounds") {
		SUBCASE("rng-valid-bounds-0-10") {
	        minBound = 0; maxBound = 10;
	    }

	    SUBCASE("rng-valid-bounds-1-1") {
	        minBound = maxBound = 1;
	    }

		SUBCASE("rng-valid-bounds-22-99") {
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
			CHECK_LT(newValue, maxBound);
			// increment counter if a match is detected
			if (oldValue == newValue)
				matchCounter++;
			// check that too many matches have not occured
			CHECK_LE(matchCounter, matchMax);
			// store new value
			oldValue = newValue;
		}
	}

	SUBCASE("rng-invalid-bounds") {
		SUBCASE("rng-invalid-bounds-n10-0") {
	        minBound = -10; maxBound = 0;
	    }

	    SUBCASE("rng-invalid-bounds-10-0") {
	        minBound = 10; maxBound = 0;
	    }

		SUBCASE("rng-invalid-bounds-1-0") {
			minBound = 1; maxBound = 0;
		}

		SUBCASE("rng-invalid-bounds-n1-100") {
			minBound = -1; maxBound = 100;
		}

		SUBCASE("rng-invalid-bounds-100-99") {
			minBound = 100; maxBound = 99;
		}

		// get new value
		newValue = rng->GetNew(minBound, maxBound);

		// confirm that error value (0) is returned
		CHECK_EQ(newValue, 0);
	}
}

TEST_SUITE_END();



TEST_SUITE_BEGIN("random-password");

TEST_CASE("random-password-constructor") {
    PasswordGenerator *pg = nullptr;
    CHECK_EQ(pg, nullptr);

    pg = new PasswordGenerator();
    REQUIRE_NE(pg, nullptr);
}

TEST_CASE("random-password") {
	PasswordGenerator *pg = new PasswordGenerator();
	std::string password = "";
	int length = 0;

	SUBCASE("random-password-valid") {
		const int maxLength = 1024;	// max length of a generated password
		const int sampleSize = 2000;	// generate many passwords for each test subcase

		SUBCASE("random-password-valid-length") {
			SUBCASE("random-password-valid-length-8") {
				length = 8;
			}

			SUBCASE("random-password-valid-length-100") {
				length = 100;
			}

			SUBCASE("random-password-valid-length-1000") {
				length = 1020;
			}

			SUBCASE("random-password-valid-length-24") {
				length = 24;
			}

			// ensure correct length
			password = pg->NewPassword(length);
			CHECK_EQ(password.length(), length);
		}

		SUBCASE("random-password-truncated-length") {
			SUBCASE("random-password-truncated-length-1025") {
				length = 1025;
			}

			SUBCASE("random-password-truncated-length-9000") {
				length = 9000;
			}

			// ensure correct length (truncated to max size)
			password = pg->NewPassword(length);
			CHECK_EQ(password.length(), maxLength);
			// update length value for future tests below
			length = maxLength;
		}

		// ensure passwords aren't empty or null
		CHECK_NE(password.length(), 0);
		CHECK_NE(password, "");

#ifdef TEST_RANDOMNESS
		// ensure passwords have reasonable level of complexity and randomness
		const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~`!@#$%^&*()_-+={[}]|:;,.?";
		int characterOccurances[characters.length()] = { 0 };

		// the amount of each character we expect to see
		int characterOccurancesExpected = (length * sampleSize) / (characters.length());
		// occurances must be within a +/- % range of expected values
		float variancePermitted = 0.50;
		int characterOccuranceVariance = (int) characterOccurancesExpected * variancePermitted;

		// run many generations to produce a large enough sample size
		for (int test = 0; test < sampleSize; test++) {
			// generate new password
			password = pg->NewPassword(length);
			// evaluate every character in the password
			for (int passwordIndex = 0; passwordIndex < length; passwordIndex++) {
				// increment the occurance counter for each character found
				for (int characterIndex = 0; characterIndex < characters.length(); characterIndex++) {
					if (password[passwordIndex] == characters[characterIndex])
						characterOccurances[characterIndex]++;
				}
			}
		}

		// now that all tests are completed, check for occurance variability
		for (int characterIndex = 0; characterIndex < characters.length(); characterIndex++) {
			CHECK_LE(characterOccurances[characterIndex], characterOccurancesExpected + characterOccuranceVariance);
			CHECK_GE(characterOccurances[characterIndex], characterOccurancesExpected - characterOccuranceVariance);
		}
#endif

		// ensure first character is not a special character
		const std::string specialCharacters = "~`!@#$%^&*()_-+={[}]|:;,.?";
		for (int characterIndex = 0; characterIndex < specialCharacters.length(); characterIndex++) {
			CHECK_NE(password[0], specialCharacters[characterIndex]);
		}
	}

	SUBCASE("random-password-invalid-length") {
		SUBCASE("random-password-invalid-length-n1") {
			length = -1;
		}

		SUBCASE("random-password-invalid-length-n2000") {
			length = -2000;
		}

		SUBCASE("random-password-invalid-length-0") {
			length = 0;
		}

		password = pg->NewPassword(length);
		REQUIRE_EQ(password.length(), 0);
		REQUIRE_EQ(password, "");
	}
}

TEST_SUITE_END();
