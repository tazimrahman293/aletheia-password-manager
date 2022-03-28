// test_2-1.cpp
// Contains the function definitions for testing User Story 2-1.
// Authors: Tyrel Kostyk

#include "auth/Authenticator.h"

#include "doctest.h"

TEST_SUITE_BEGIN("auth");

TEST_CASE("auth-construct") {
	Authenticator *auth = nullptr;
    CHECK_EQ(auth, nullptr);

    auth = new Authenticator();
    REQUIRE_NE(auth, nullptr);
}


TEST_CASE("auth-hash-and-verify") {
	Authenticator *auth = new Authenticator();
	const int hashSize = 128;
	const int sampleSize = 10;

	std::string password = "";
	std::string passwordAttempt = "";
	std::vector<uint8_t> hash[sampleSize];
	bool valid = false;

	SUBCASE("auth-hash-and-verify-valid-password") {
		SUBCASE("auth-hash-and-verify-valid-password-normal") {
			password = "password";
		}

		SUBCASE("auth-hash-and-verify-valid-password-special") {
			password = "pa$$word1234567890______~`!@#$%^&*()_-+={[}]|:;,.?";
		}

		SUBCASE("auth-hash-and-verify-valid-password-short") {
			password = "p";
		}

		SUBCASE("auth-hash-and-verify-valid-password-long") {
			password = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		}

		// create many unique hashes for the same password
		for (int i = 0; i < sampleSize; i++) {
			hash[i] = auth->Hash(password);

			// check that hash is correct size
			CHECK_EQ(hash[i].size(), hashSize);

			// check that all hashes are unique
			for (int j = 1; i-j >= 0; j++) {
				CHECK_NE(hash[i], hash[i-j]);
			}

			// check that new hash still validates password
			valid = auth->Verify(hash[i], password);
			CHECK(valid);

			// check that an invalid password does not get validated
			passwordAttempt = "__";
			valid = auth->Verify(hash[i], passwordAttempt);
			CHECK(!valid);
		}
	}

	SUBCASE("auth-hash-and-verify-invalid-password") {
		password = "";
		for (int i = 0; i < sampleSize; i++) {
			hash[i] = auth->Hash(password);

			// check that hash is expected size (0 for empty password)
			CHECK_EQ(hash[i].size(), 0);
		}
	}

}

TEST_SUITE_END();
