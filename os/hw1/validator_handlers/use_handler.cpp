#include <use_handler.h>

#include <iostream>
#include <validators/definition.h> // is_valid_symbol, is_valid_relative_address
#include <validators/use.h> // is_valid_token_count

unsigned int use_handler(char* p_token, unsigned int count, bool onlyEvaluateCount)
{
	if(onlyEvaluateCount)
	{
		return UseValidator::is_valid_token_count(p_token);
	}

	unsigned int result = 0;
	if (count > 0) // this should never resolve to false
	{
		// NOTE: Use List is made up of Definition Symbols, which is why we use DefinitionValidator class's implementation
		result= DefinitionValidator::is_valid_symbol(p_token);
		cout << "is_valid_symbol: " << result << endl;
	}
	return result;
}
