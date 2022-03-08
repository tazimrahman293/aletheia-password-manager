// unit_test_suite.cpp
// Contains the main entrypoint for the Unit Test Suite for the Aletheia password manager project.
// Authors: Tyrel Kostyk,


#include <test.h>
#include <test_5-1.h>


int main(int argc, char *argv[])
{
	int errorCount = 0;
	int success = TEST_SUCCESS;

	/* TEST USER STORY 5-1 */

	success = test_5_1_RandomNumberGeneratorConstructor();
	if (success != TEST_SUCCESS)
		errorCount++;

	success = test_5_1_RandomNumberGeneratorBounds();
	if (success != TEST_SUCCESS)
		errorCount++;

	/* PRINT RESULTS */

	if (errorCount > 0)
		printf("Test Suite Failed: %d errors encountered\n", errorCount);
	else
		printf("Test Suite Passed! Good job :)\n");
}
