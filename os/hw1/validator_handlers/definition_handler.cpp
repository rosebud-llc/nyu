#include <definition_handler.h>

#include <iostream>
#include <stdlib.h> //strtoul
#include <validators/definition.h> // is_valid_symbol, is_valid_relative_address


unsigned int definition_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData,
		bool onlyEvaluateCount)
{
	if (onlyEvaluateCount)
	{
		return DefinitionValidator::is_valid_token_count(p_token);
	}

	unsigned int result = 0;
	if (validator->tokenCount > 0) // this should never resolve to false
	{
		if (validator->tokenCount % 2 == 0)
		{
			result = DefinitionValidator::is_valid_symbol(p_token);
			// Asumes we have reached state where result is valid:
			if(result == 0)
			{
				// If we've seen symbol before, this call will handle marking as dupe
				symbolTable.insert_symbol_into_table(p_token);
				// Do not add to ModuleData._defList if dupe - otherwise Program -> set_validator_count will incorrectly overwrite address
				if (!symbolTable.is_duplicate(p_token))
				{
					moduleData.insert_symbol_to_def_list(p_token);
				}
				else
				{
					//cout << "Warning: not inserting symbol into _defList because isDuplicate == true" << endl;
				}
			}
			cout << "is_valid_symbol: " << result << endl;
		}
		else
		{
			result = DefinitionValidator::is_valid_relative_address(p_token, validator);
			// Assuming result is valid && the relative address hasn't already been set - prevents overwriting address if isDuplicate
			if (result == 0 && !symbolTable.is_duplicate(validator->prevToken))
			{
				unsigned long relativeAddress0 = strtoul(p_token,NULL,0);
				unsigned int relativeAddress1 = (unsigned int)relativeAddress0;
				symbolTable.update_symbol_relative_address(validator->prevToken, relativeAddress1);
			}
			cout << "is_valid_relative_address: " << result << endl;
		}
	}
	return result;
}
