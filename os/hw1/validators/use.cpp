#include <use.h>

#include <iostream> // cout, endl
#include <stdlib.h> // strtoul

//static
unsigned int UseValidator::is_valid_token_count(char* p_token)
{
	cout << "Validating Token Count: " << p_token << endl;

	unsigned int result = 0;

	result = UseValidator::is_valid_number(p_token);
	if (result > 0)
	{
		return result;
	}

	static const unsigned int errorTooManyUse = 6;
	static const unsigned int maxTokenCount = 16;
	if (!UseValidator::is_valid_number_size(p_token, maxTokenCount))
	{
		result = errorTooManyUse;
	}
	cout << "Token Count Validation Result: " << result << endl;
	return result;
}

bool UseValidator::process(char* p_token) const
{
	cout << "UseValidator processing: " << p_token << endl;
	return true;
}

UseValidator::ValidatorType::validator_enum UseValidator::get_validator_enum() const
{
	cout << "UseValidator ENUM: " << validatorType.USE << endl;
	return validatorType.USE;
}

void UseValidator::append_symbol(string& symbol)
{
	_symbols.push_back(symbol);
}

unsigned int UseValidator::get_symbols_count()
{
	return _symbols.size();
}
