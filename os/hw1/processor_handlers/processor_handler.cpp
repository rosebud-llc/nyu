#include <processor_handler.h>

#include <iostream>

#include <definition_processor.h>
#include <use_processor.h>
#include <program_processor.h>

// Return true on success | false on failure
unsigned int processor_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData)
{
	unsigned int validatorType = validator->validatorType;
	unsigned int result = 0;

	// Process Definition Set
	if (validatorType == 0)
	{
		//cout << "Process Definition List" << endl;
		result = definition_processor(p_token,
				validator,
				moduleData);
		//cout << "Process Definition List Result: " << result << endl;
	}
	// Process Use List
	else if (validatorType == 1)
	{
		//cout << "Process Use List Handler" << endl;
		result = use_processor(p_token,
				moduleData);
		//cout << "Process Use List Result: " << result << endl;
	}
	// Process Program Instructions
	else if (validatorType == 2)
	{
		//cout << "Processing Program Instructions" << endl;
		result = program_processor(p_token, 
				validator,
				symbolTable, 
				moduleData);
		//cout << "Process Program Instructions Result: " << result << endl;
	}
	// Unknown Processor Type
	else
	{
		cout << "ERROR: Unknown processor type: " << validatorType << endl;
	}
	return result;
}
