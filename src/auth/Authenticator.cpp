// Authenticator.h
// Contains the class definition for Authentication and Encryption.
// Authors: Tyrel Kostyk

#include <aletheia.h>
#include <auth/Authenticator.h>
#include <hydrogen.h>
#include <stdlib.h>
#include <cstring>


/**
 * Construct an Authenticator object, initializing the hydrogen encryption
 * library and creating a local private key in the process.
 */
Authenticator::Authenticator()
{
	// initialize the libhydrogen encryption library
	if (hydro_init() != 0) {
		printf("Failed to initialize Hydrogren encryption library. Exiting...\n");
		exit(-1);
	}
}


/**
 * Create an encrypted message that represents the provided plaintext password.
 * @param password	A plaintext password.
 * @return A byte vector containing the new encrypted message.
 */
std::vector<uint8_t> Authenticator::Encrypt(const std::string &password)
{
	// password must have non-zero length
	if (password.length() <= 0)
		return {};

	// create a byte array for storing resultant encrypted message
	int encryptedSize = encryptedOverhead + password.length();
	uint8_t *encryptedBytes = (uint8_t *)malloc(encryptedSize);
	if (encryptedBytes == nullptr)
		return std::vector<uint8_t>();;
	memset(encryptedBytes, 0, encryptedSize);

	// generate the encrypted message
	int result = hydro_secretbox_encrypt(encryptedBytes, password.c_str(),
		password.length(), encryptId, context, masterKey);

	// return an empty vector if the creation attempt failed
	if (result != 0) {
		free(encryptedBytes);
		return std::vector<uint8_t>();
	}

	// return a vector containing the encrypted password
	std::vector<uint8_t> encrypted(encryptedBytes, encryptedBytes + encryptedSize);
	free(encryptedBytes);
	return encrypted;
}


/**
 * Decrypts and verifies the integreity of an encrypted password.
 * @param encrypted A byte-vector containing an encrypted password.
 * @returns A string containing the decrypted password on success; empty string otherwise.
 */
std::string Authenticator::Decrypt(const std::vector<uint8_t> &encrypted)
{
	// decrypted password to return
	std::string password = "";

	// convert the encrypted message to a simple byte array
	const uint8_t *encryptedBytes = &encrypted[0];

	// prepare a byte array to receive the decrypted message
	int decryptedSize = encrypted.size() - encryptedOverhead;
	char *decryptedString = (char *)malloc(decryptedSize);
	if (decryptedString == nullptr)
		return password;
	memset(decryptedString, 0, decryptedSize);

	// verify and decrypt the password
	int result = hydro_secretbox_decrypt(decryptedString, encryptedBytes,
		encrypted.size(), encryptId, context, masterKey);

	// convert char array to std::string upon success
	if (result == 0) {
		for (int i = 0; i < decryptedSize; i++)
			password += decryptedString[i];
	}

	free(decryptedString);
	return password;
}
