#include <definition.h>

#include <iostream> // cout, endl
#include <locale>   // isalnum, isdigit
#include <string.h> // strlen
#include <stdlib.h> // strtoul


//static
unsigned int DefinitionValidator::is_valid_token_count(char* p_token)
{
	//cout << "Validating Token Count: " << p_token << endl;

	unsigned int result = 0;

	result = DefinitionValidator::is_valid_number(p_token);
	if (result > 0)
	{
		return result;
	}

	static const unsigned int errorTooManyDef = 5;
	static const unsigned int maxTokenCount = 16;
	if (!DefinitionValidator::is_valid_number_size(p_token, maxTokenCount))
	{
		result = errorTooManyDef;
	}
	//cout << "Token Validation Result: " << result << endl;
	return result;
}


//static
unsigned int DefinitionValidator::is_valid_relative_address(char* p_token,
		ValidatorData* validator)
{
	//cout << "Validating Relative Address: " << p_token << endl;

	unsigned int result = 0;
	static const unsigned int errorNumExpected = 1;

	locale loc;
	unsigned int token_length = strlen(p_token);
	//TODO: add a check if relative address too big / long?
	for(unsigned int i = 0; i < token_length; ++i)
	{
		if (!isdigit(p_token[i],loc))
		{
			//cout << "ERROR: Invalid digit: " << p_token[i] << endl;
			result = errorNumExpected;
			//cout << "Address Validation Result: " << result << endl;
			return result;
		}
	}
	//cout << "Address Validation Result: " << result << endl;
	return result;
}

