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


TEST_CASE("auth-encrypt-and-verify") {
	Authenticator *auth = new Authenticator();

	const int overheadSize = 36;
	const int sampleSize = 10;

	int encryptedSize = 0;

	std::string password = "";
	std::string passwordDecrypted = "";
	std::vector<uint8_t> encrypted[sampleSize];

	SUBCASE("auth-encrypt-and-verify-valid-password") {
		SUBCASE("auth-encrypt-and-verify-valid-password-normal") {
			password = "password";
		}

		SUBCASE("auth-encrypt-and-verify-valid-password-numbers") {
			password = "01234567899876543210";
		}

		SUBCASE("auth-encrypt-and-verify-valid-password-special") {
			password = "pa$$word1234567890______~`!@#$%^&*()_-+={[}]|:;,.?";
		}

		SUBCASE("auth-encrypt-and-verify-valid-password-short") {
			password = "p";
		}

		SUBCASE("auth-encrypt-and-verify-valid-password-long") {
			password = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		}

		// calculate the encrypted size
		encryptedSize = password.length() + overheadSize;

		// create many unique encryptions for the same password
		for (int i = 0; i < sampleSize; i++) {
			encrypted[i] = auth->Encrypt(password);

			// check that encryption is correct size
			CHECK_EQ(encrypted[i].size(), encryptedSize);

			// check that all encryptions are unique
			for (int j = 1; i-j >= 0; j++) {
				CHECK_NE(encrypted[i], encrypted[i-j]);
			}

			// check that new encryption still validates password
			passwordDecrypted = auth->Decrypt(encrypted[i]);
			CHECK_EQ(passwordDecrypted, password);
		}
	}

	SUBCASE("auth-encrypt-and-verify-invalid-password") {
		password = "";
		for (int i = 0; i < sampleSize; i++) {
			encrypted[i] = auth->Encrypt(password);

			// check that encryption is expected size (0 for empty password)
			CHECK_EQ(encrypted[i].size(), 0);
		}
	}

}

TEST_SUITE_END();
