// RandomNumberGenerator.cpp
// Contains the class definition for generating random numbers.
// Authors: Tyrel Kostyk

#include <random/RandomNumberGenerator.h>
#include <hydrogen.h>


/**
 * Constructor for the RandomNumberGenerator class.
 */
RandomNumberGenerator::RandomNumberGenerator()
{
	// initial seed
	Seed();
}


/**
 * Generate and return a random number from with a range.
 *
 * @param minValue The minimum value of the random number (inclusive).
 * @param maxValue The maximum value of the random number (inclusive).
 * @return A random value within the bounds specified above. 0 on error.
 */
int RandomNumberGenerator::GetNew(int minValue, int maxValue)
{
    if (minValue == maxValue)
        return maxValue;
	if (minValue < 0 || maxValue < 0)
		return 0;
	if (minValue > maxValue)
		return 0;

	// reseed before random generation
	Seed();

	// generate random value between bounds
	int randomNumber = (hydro_random_u32() % (maxValue - minValue)) + minValue;

	return randomNumber;
}


/**
 * Seed the randomizer.
 */
void RandomNumberGenerator::Seed()
{
	hydro_random_reseed();
}
