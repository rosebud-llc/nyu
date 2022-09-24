#include <base.h>

#include <iostream> // cout, endl
#include <string.h> // strlen
#include <locale>   // isdigit
#include <stdlib.h> // strtoul

//static
unsigned int BaseValidator::is_valid_number(char* p_token)
{
	//cout << "Validating Token Number: " << p_token << endl;

	unsigned int result = 0;
	static const unsigned int errorNumExpected = 1;

	locale loc;
	unsigned int tokenLength = strlen(p_token);
	for(unsigned int i = 0; i < tokenLength; ++i)
	{
		if (!isdigit(p_token[i],loc))
		{
			cout << "ERROR: Invalid digit: " << p_token[i] << endl;
			result = errorNumExpected;
			//cout << "Token Number Validation Result: " << result << endl;
			return result;
		}
	}
	return result;
}

//static
bool BaseValidator::is_valid_number_size(char* p_token,
		unsigned int maxTokenCount)
{
	//cout << "Validating Token Number Size: " << p_token << endl;

	unsigned long tokenCount = strtoul(p_token,NULL,0);
	//cout << "Converted p_token from " << p_token << " to " << tokenCount << endl;
	return tokenCount < maxTokenCount;
}
