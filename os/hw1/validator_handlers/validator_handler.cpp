#include <validator_handler.h>

#include <iostream>

#include <definition_handler.h>
#include <use_handler.h>
#include <program_handler.h>

// Return true on success | false on failure
unsigned int validator_handler(char* p_token, ValidatorData* validator, bool onlyEvaluateCount)
{
	unsigned int validatorType = validator->validatorType;
	unsigned int tokenCount = validator->tokenCount;

	unsigned int result = 0;

	// Definition Handler
	if (validatorType == 0)
	{
		result = definition_handler(p_token, tokenCount, onlyEvaluateCount);
	}
	// Use Handler
	else if (validatorType == 1)
	{
		result = use_handler(p_token, tokenCount, onlyEvaluateCount);
	}
	// Program Handler
	else if (validatorType == 2)
	{
		result = program_handler(p_token, tokenCount, onlyEvaluateCount);
	}
	// Unknown Validator Type
	else
	{
		cout << "ERROR: Unknown validator type: " << validatorType << endl;
	}
	return result;
}
