#include <definition_handler.h>

#include <iostream>
#include <validators/definition.h> // is_valid_symbol, is_valid_relative_address


unsigned int definition_handler(char* p_token, unsigned int count, bool onlyEvaluateCount)
{
	if (onlyEvaluateCount)
	{
		return DefinitionValidator::is_valid_token_count(p_token);
	}

	unsigned int result = 0;
	if (count > 0) // this should never resolve to false
	{
		if (count % 2 == 0)
		{
			result = DefinitionValidator::is_valid_symbol(p_token);
			cout << "is_valid_symbol: " << result << endl;
		}
		else
		{
			result = DefinitionValidator::is_valid_relative_address(p_token);
			cout << "is_valid_relative_address: " << result << endl;
		}
	}
	return result;
}
