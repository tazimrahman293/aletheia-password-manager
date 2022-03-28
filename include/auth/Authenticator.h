// Authenticator.h
// Contains the class definition for Authentication and Encryption.
// Authors: Tyrel Kostyk

#ifndef TBD_AUTH_H
#define TBD_AUTH_H

#include <stdint.h>
#include <string>
#include <vector>


class Authenticator {
private:
	// static flags for libhydrogen hashing calls
	const int opsLimit = 50000;
	const int memLimit = 0;
	const int threads = 0;

	const int hashSize = 128;					// size of generated hashes (in bytes)

	static const int masterKeySize = 32;		// size of master key (in bytes)
	uint8_t masterKey[masterKeySize] = { 0 };	// master key

public:
	Authenticator();
	~Authenticator() = default;

	std::vector<uint8_t> Hash(const std::string &password);
	bool Verify(std::vector<uint8_t> hash, const std::string &password);
};



#endif  // TBD_AUTH_H
