// test_5-1.cpp
// Contains the function definitions for testing User Story 5-1.
// Authors: Tyrel Kostyk

#include <test.h>
#include <test_5-1.h>


/*******************************************************************************
                             PRIVATE FUNCTION STUBS
*******************************************************************************/

static int test_5_1_RandomNumberGeneratorConstructor(void);
static int test_5_1_RandomNumberGeneratorBounds(void);


/*******************************************************************************
                                   PUBLIC API
*******************************************************************************/

/**
 * Run all of the individual test cases for User Story 5-1.
 * @return The error count of the internal test cases that failed.
 */
int test_5_1_testAll(void)
{
	int errorCount = 0;

	if (test_5_1_RandomNumberGeneratorConstructor() != TEST_SUCCESS)
		errorCount++;

	if (test_5_1_RandomNumberGeneratorBounds() != TEST_SUCCESS)
		errorCount++;

	return errorCount;
}

/*******************************************************************************
                               PRIVATE FUNCTIONS
*******************************************************************************/

/**
 * Test that the RandomNumberGenerator object can construct correctly.
 */
static int test_5_1_RandomNumberGeneratorConstructor(void)
{
	// create a pointer to a RandomNumberGenerator object
	RandomNumberGenerator *rng = nullptr;

	// construct the RandomNumberGenerator object
	rng = new RandomNumberGenerator();

	// assert that the object is not null (and thus constructed correctly)
	if (rng == nullptr) {
		printf("test_5_1_RandomNumberGeneratorConstructor: constructed object is null\n");
		return TEST_FAILURE;
	}

	// test passes
	return TEST_SUCCESS;
}


/**
 * Test that the RandomNumberGenerator can produce numbers within given bounds.
 */
static int test_5_1_RandomNumberGeneratorBounds(void)
{
	// construct a RandomNumberGenerator object
	RandomNumberGenerator *rng = new RandomNumberGenerator();

	// assert that it constructed correctly
	if (rng == nullptr) {
		printf("test_5_1_RandomNumberGeneratorBounds: constructed object is null\n");
		return TEST_FAILURE;
	}

	// define initial bounds (note: bounds are inclusive)
	int minBound = 20;
	int maxBound = 100;

	// get a new value
	int newValue1 = rng->GetNew(minBound, maxBound);

	// assert that number is within (or including) bounds
	if (newValue1 < minBound) {
		printf("test_5_1_RandomNumberGeneratorBounds: Random number is too small (expected greater than %d, got %d)\n", minBound, newValue1);
		return TEST_FAILURE;
	} else if (newValue1 > maxBound) {
		printf("test_5_1_RandomNumberGeneratorBounds: Random number is too large (expected smaller than %d, got %d)\n", maxBound, newValue1);
		return TEST_FAILURE;
	}

	return TEST_SUCCESS;
}
