// RandomNumberGenerator.cpp
// Contains the class definition for generating random numbers.
// Authors: Tyrel Kostyk

#include <random/RandomNumberGenerator.h>

#include <exceptions>
#include <stdlib.h>
#include <time.h>


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
 * @return A random value within the bounds specified above.
 */
int RandomNumberGenerator::GetNew(int minValue, int maxValue)
{
    if (minValue == maxValue)
        return maxValue;

	// seed the randomizer
	Seed();

	// generate random value within bounds
	int randomNumber = (rand() % (maxValue - minValue)) + minValue;

	return randomNumber;
}


/**
 * Seed the randomizer.
 */
void RandomNumberGenerator::Seed()
{
	// seed the randomizer with the current time
	srand(time(NULL));
}
