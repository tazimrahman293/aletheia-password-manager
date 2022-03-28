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
std::string PasswordGenerator::NewPassword(int length, bool lower, bool upper, bool number, bool special)
{
	int characterOption = 0;			// index of which character to choose
	std::string password = "";			// the password to be generated and returned
	std::string characterOptions = "";	// string of all available characters

	// password must be of positive non-zero length
	if (length <= 0)
		return password;

	// all passwords require at least ONE OF: lower, upper, number
	if (lower == false && upper == false && number == false)
		return password;

	// concat string options together based on selected input
	if (lower)
		characterOptions += characters[alphanumericOptionsLower];
	if (upper)
		characterOptions += characters[alphanumericOptionsUpper];
	if (number)
		characterOptions += characters[alphanumericOptionsNumber];
	if (special)
		characterOptions += characters[alphanumericOptionsSpecial];

	for (int index = 0; index < length; index++)
	{
		// enforce maximum password length rules
		if (index == maxLength)
			return password;

		// initial character can be lower, upper, or number (not a special symbol)
		if (index == 0 && special == true)
			characterOption = random->GetNew(0, characterOptions.length() - characters[alphanumericOptionsSpecial].length());
		// all other characters can include special symbols
		else
			characterOption = random->GetNew(0, characterOptions.length());

		// add the new character to the password
		password += characterOptions[characterOption];
	}

	return password;
}
