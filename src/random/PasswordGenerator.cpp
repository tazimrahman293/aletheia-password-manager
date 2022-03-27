// PasswordGenerator.cpp
// Contains the class definition for generating randomized Strings (to be used
// for random password generation).
// Authors: Tyrel Kostyk

#include <random/PasswordGenerator.h>
#include <random/RandomNumberGenerator.h>


/**
 * Constructor for the PasswordGenerator class.
 */
PasswordGenerator::PasswordGenerator()
{
	// initialize a Random Number Generator object
	random = new RandomNumberGenerator();
}


/**
 * Generates a new random password string.
 *
 * @param length The requested length of the password. Will be truncated if this
 *               exceeds the internally defined maximum length.
 * @return A randomly generated password string.
 */
std::string PasswordGenerator::NewPassword(int length)
{
	int alphanumericOption = 0;	// what type of character (lowercase, etc.)
	int characterOption = 0;	// which character within this type
	std::string password = "";	// the password to be generated and returned

	if (length <= 0)
		return password;

	for (int index = 0; index < length; index++)
	{
		// enforce maximum password length rules
		if (index == maxLength)
			return password;

		// initial character can be lower, upper, or number (not a symbol)
		if (index == 0)
			alphanumericOption = random->GetNew(0, alphanumericOptionsNumber);
		// all other characters can include special symbols
		else
			alphanumericOption = random->GetNew(0, alphanumericOptionsCount-1);

		// determine which character to place
		characterOption = random->GetNew(0, characters[alphanumericOption].length()-1);

		// add the new character to the password
		password += characters[alphanumericOption][characterOption];
	}

	return password;
}
