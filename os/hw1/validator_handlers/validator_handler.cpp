#include <validator_handler.h>

#include <iostream>

#include <definition_handler.h>
#include <use_handler.h>
#include <program_handler.h>

// Return true on success | false on failure
unsigned int validator_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData,
		bool onlyEvaluateCount)
{
	unsigned int validatorType = validator->validatorType;
	unsigned int tokenCount = validator->tokenCount;

	unsigned int result = 0;

	// Definition Handler
	if (validatorType == 0)
	{
		//TODO rm tokenCount and just pass validator
		cout << "Definition Handler" << endl;
		result = definition_handler(p_token, validator, symbolTable, moduleData, onlyEvaluateCount);
		cout << "Definition Handler Result: " << result << endl;
	}
	// Use Handler
	else if (validatorType == 1)
	{
		//TODO rm tokenCount and just pass validator
		cout << "Use Handler" << endl;
		//cout << "Only Evaluate Count? " << onlyEvaluateCount << endl;
		result = use_handler(p_token, tokenCount, onlyEvaluateCount);
		cout << "Use Handler Result: " << result << endl;
	}
	// Program Handler
	else if (validatorType == 2)
	{
		//TODO rm tokenCount and just pass validator
		cout << "Program Handler" << endl;
		result = program_handler(p_token, 
				tokenCount, 
				moduleData,
				onlyEvaluateCount);
		cout << "Program Handler Result: " << result << endl;
	}
	// Unknown Validator Type
	else
	{
		//cout << "ERROR: Unknown validator type: " << validatorType << endl;
	}
	return result;
}
