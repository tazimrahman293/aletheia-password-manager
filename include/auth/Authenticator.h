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
	// context (change not supported; kept constant)
	static const int contextSize = 32;
	const char context[contextSize] = { "aletheia" };

	// message ID for encrypted messages (change not supported; kept at 0)
	const int encryptId = 0;

	// size of overhead for each encryption (in bytes)
	const int encryptedOverhead = 36;

	// max size of a (decrypted, plaintext) password
	const int decryptedMaxSize = 1024;

	// hardcoded master key
	static const int masterKeySize = 32;
	const uint8_t masterKey[masterKeySize] = {
		0xF5, 0xB9, 0xC3, 0xEC, 0x5E, 0xB1, 0x3D, 0x56,
		0x56, 0xD3, 0x87, 0x57, 0xC0, 0xA0, 0xFA, 0x46,
		0xA1, 0x7D, 0x2E, 0xA3, 0x45, 0x60, 0x8B, 0xE8,
		0x6D, 0xED, 0x54, 0x80, 0x51, 0x81, 0xC3, 0x2C
	};

public:
	Authenticator();
	~Authenticator() = default;

	std::vector<uint8_t> Encrypt(const std::string &password);
	std::string Decrypt(const std::vector<uint8_t> &encrypted);
};



#endif  // TBD_AUTH_H
