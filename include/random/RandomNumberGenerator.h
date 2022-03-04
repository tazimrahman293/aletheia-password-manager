// RandomNumberGenerator.h
// Contains the class definition for generating random numbers.
// Authors: Tyrel Kostyk

#ifndef RANDOM_H
#define RANDOM_H


/**
 * A class that provides an API for generating random numbers.
 */
class RandomNumberGenerator {

	void Seed();

public:

	RandomNumberGenerator();
	~RandomNumberGenerator() = default;

	int GetNew(int minValue, int maxValue);

};

#endif // RANDOM_H
