// PasswordGenerator.h
// Contains the class definition for generating randomized Strings (to be used
// for random password generation).
// Authors: Tyrel Kostyk

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <string>

class RandomNumberGenerator;

/**
 * A class that provides an API for generating random variable-length passwords.
 */
class PasswordGenerator {

	// define indices for difference alphanumeric options
	enum alphanumericOptions {
		alphanumericOptionsLower = 0,	// lowercase characters
		alphanumericOptionsUpper = 1,	// uppercase characters
		alphanumericOptionsNumber = 2,	// numeric characters
		alphanumericOptionsSpecial = 3,	// special symbol characters
		alphanumericOptionsCount = 4,	// the number of alphanumeric options
	};

	// an array of strings holding all of the possible characters, organized by type
	const std::string characters[alphanumericOptionsCount] = {
		"abcdefghijklmnopqrstuvwxyz",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"0123456789",
		"~`!@#$%^&*()_-+={[}]|:;,.?"
	};

	// max length of a request password string
	const int maxLength = 1024;

	// random number generator (for choosing characters/types at random)
	RandomNumberGenerator* random = nullptr;

public:
	PasswordGenerator();
	~PasswordGenerator() = default;

	std::string NewPassword(int length, bool lower=true, bool upper=true, bool number=true, bool special=true);

};

#endif // PASSWORDGENERATOR_H
