#include <use_handler.h>

#include <iostream>
#include <validators/use.h> // is_valid_token_count

unsigned int use_handler(char* p_token,
		unsigned int count,
		bool onlyEvaluateCount)
{
	//cout << "Use Handler Token: " << p_token << endl;
	if(onlyEvaluateCount)
	{
		//cout << "Evaluate Use Handler Count TRUE. Evaluating: " << p_token << endl;
		return UseValidator::is_valid_token_count(p_token);
	}

	unsigned int result = 0;
	if (count > 0) // this should never resolve to false
	{
		// NOTE: Use List is made up of Definition Symbols, which is why we use DefinitionValidator class's implementation
		result = UseValidator::is_valid_symbol(p_token);
		cout << "is_valid_symbol: " << result << endl;
	}
	return result;
}
