// Authenticator.h
// Contains the class definition for Authentication and Encryption.
// Authors: Tyrel Kostyk

#include <aletheia.h>
#include <auth/Authenticator.h>
#include <hydrogen.h>


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

	// create the local master key
	hydro_pwhash_keygen(masterKey);
}


/**
 * Create a high-entropy hash that represents the provided plaintext password.
 * @param password	A plaintext password that can later be validated against this hash.
 * @return A byte vector containing the new hash.
 */
std::vector<uint8_t> Authenticator::Hash(std::string password)
{
	// create a byte array for storing resultant hash
	uint8_t hashBytes[hashSize] = { 0 };

	// generate the hash
	int result = hydro_pwhash_create(hashBytes, password.c_str(),
		password.length(), masterKey, opsLimit, memLimit, threads);

	// return an empty vector if the creation attempt failed
	if (result != 0)
		return std::vector<uint8_t>();

	// return a vector containing the hash
	std::vector<uint8_t> hash(hashBytes, hashBytes + hashSize);
	return hash;
}


/**
 * Verifies the integreity of a password attempt against an existing hash.
 * @param hash A byte-vector containing an existing hash.
 * @param passwordAttempt A plaintext string of the password to verify.
 * @returns true (1) on success & verified, false (0) otherwise.
 */
bool Authenticator::Verify(std::vector<uint8_t> hash, std::string passwordAttempt)
{
	// convert the hash to a simple byte array
	uint8_t *hashBytes = &hash[0];

	// verify the hash against the password attempt
	int result = hydro_pwhash_verify(hashBytes, passwordAttempt.c_str(),
		passwordAttempt.length(), masterKey, opsLimit, memLimit, threads);

	// return the success of the attempt
	return (result == 0);
}
