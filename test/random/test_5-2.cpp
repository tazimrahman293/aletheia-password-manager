// test_5-2.cpp
// Contains the function definitions for testing User Story 5-2.
// Authors: Tyrel Kostyk

#include "random/PasswordGenerator.h"

#include "doctest.h"


TEST_SUITE_BEGIN("random-password-custom");

TEST_CASE("random-password-custom") {
	PasswordGenerator *pg = new PasswordGenerator();
	std::string password = "";
	int length = 0;
	bool lower = true;
	bool upper = true;
	bool number = true;
	bool special = true;

	SUBCASE("random-password-custom-valid") {
		const int maxLength = 1024;	// max length of a generated password
		const std::string lowerCharacters = "abcdefghijklmnopqrstuvwxyz";
		const std::string upperCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string numberCharacters = "0123456789";
		const std::string specialCharacters = "~`!@#$%^&*()_-+={[}]|:;,.?";

		SUBCASE("random-password-custom-valid-length") {
			SUBCASE("random-password-custom-valid-length-8-all") {
				length = 8;
				lower = true;
				upper = true;
				number = true;
				special = true;
			}

			SUBCASE("random-password-custom-valid-length-8-no-lower") {
				length = 8;
				lower = false;
				upper = true;
				number = true;
				special = true;
			}

			SUBCASE("random-password-custom-valid-length-100-no-lower-no-upper") {
				length = 100;
				lower = false;
				upper = false;
				number = true;
				special = true;
			}

			SUBCASE("random-password-custom-valid-length-24-no-special") {
				length = 24;
				lower = true;
				upper = true;
				number = true;
				special = false;
			}

			SUBCASE("random-password-custom-valid-length-24-no-number-no-special") {
				length = 24;
				lower = true;
				upper = true;
				number = false;
				special = false;
			}

			SUBCASE("random-password-custom-valid-length-24-no-lower-no-number") {
				length = 24;
				lower = false;
				upper = true;
				number = false;
				special = true;
			}

			// ensure correct length
			password = pg->NewPassword(length, lower, upper, number, special);
			CHECK_EQ(password.length(), length);
		}

		SUBCASE("random-password-custom-truncated-length") {
			SUBCASE("random-password-custom-truncated-length-1025-only-numbers") {
				length = 1025;
				lower = false;
				upper = false;
				number = true;
				special = false;
			}

			SUBCASE("random-password-custom-truncated-length-9000-no-special") {
				length = 9000;
				lower = true;
				upper = true;
				number = true;
				special = false;
			}

			// ensure correct length (truncated to max size)
			password = pg->NewPassword(length, lower, upper, number, special);
			CHECK_EQ(password.length(), maxLength);
			length = maxLength;
		}

		// ensure passwords aren't empty or null
		CHECK_NE(password.length(), 0);
		CHECK_NE(password, "");

		// ensure first character is not a special character
		for (int characterIndex = 0; characterIndex < specialCharacters.length(); characterIndex++) {
			CHECK_NE(password[0], specialCharacters[characterIndex]);
		}

		// ensure that custom options were adhered to; check every character in password
		for (int passwordIndex = 0; passwordIndex < length; passwordIndex++) {
			// check for lowercase characters
			if (lower == false) {
				for (int characterIndex = 0; characterIndex < lowerCharacters.length(); characterIndex++) {
					CHECK_NE(password[passwordIndex], lowerCharacters[characterIndex]);
				}
			}
			// check for upercase characters
			if (upper == false) {
				for (int characterIndex = 0; characterIndex < upperCharacters.length(); characterIndex++) {
					CHECK_NE(password[passwordIndex], upperCharacters[characterIndex]);
				}
			}
			// check for numeric characters
			if (number == false) {
				for (int characterIndex = 0; characterIndex < numberCharacters.length(); characterIndex++) {
					CHECK_NE(password[passwordIndex], numberCharacters[characterIndex]);
				}
			}
			// check for special characters
			if (special == false) {
				for (int characterIndex = 0; characterIndex < specialCharacters.length(); characterIndex++) {
					CHECK_NE(password[passwordIndex], specialCharacters[characterIndex]);
				}
			}
		}
	}

	SUBCASE("random-password-custom-invalid") {
		SUBCASE("random-password-custom-invalid-only-special") {
			length = 24;
			lower = false;
			upper = false;
			number = false;
			special = true;
		}

		SUBCASE("random-password-custom-invalid-no-options") {
			length = 24;
			lower = false;
			upper = false;
			number = false;
			special = false;
		}

		password = pg->NewPassword(length, lower, upper, number, special);
		CHECK_EQ(password.length(), 0);
		CHECK_EQ(password, "");
	}
}

TEST_SUITE_END();
