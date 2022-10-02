#include <symbol.h>

#include <iostream> // cout, endl
#include <locale>   // isalnum, isdigit
#include <string.h> // strlen
#include <stdlib.h> // strtoul



//static
unsigned int SymbolValidator::is_valid_symbol(char* p_token)
{
	unsigned int result = 0;
	static const unsigned int errorSymExpected = 2;
	static const unsigned int errorSymTooLong  = 4;

	if (p_token == 0)
	{
		//cout << "ERROR: Invalid Symbol. Token is null." << endl;
		return errorSymExpected;
	}

	//cout << "Validating Symbol: " << p_token << endl;

	static const unsigned int max_token_length = 16;
	unsigned int token_length = strlen(p_token);
	if (token_length > max_token_length)
	{
		//cout << "ERROR: Invalid Symbol. Symbol length is greater than " << max_token_length << " characters." << endl;
		result = errorSymTooLong;
		return result;
	}

	for(unsigned int i = 0; i < token_length; ++i)
	{
		if (i == 0)
		{
			if (!isalpha(p_token[i]))
			{
				//cout << "ERROR: Invalid Symbol. First char is not alphabetic: " << p_token[i] << endl;
				result = errorSymExpected;
				return result;
			}
			continue;
		}
		if (!isalnum(p_token[i]))
		{
			//cout << "ERROR: Invalid Symbol. Symbol is not alphanumeric: " << p_token[i] << endl;
			result = errorSymExpected;
			return result;
		}
	}

	//cout << "Symbol Validation Result: " << result << endl;
	return result;
}

void SymbolValidator::set_symbol(string& symbol)
{
	_symbol = symbol;
}

string SymbolValidator::get_symbol()
{
	return _symbol;
}
