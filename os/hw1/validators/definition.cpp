#include <definition.h>

#include <iostream> // cout, endl
#include <locale>   // isalnum, isdigit
#include <string.h> // strlen
#include <stdlib.h> // strtoul


//static
unsigned int DefinitionValidator::is_valid_token_count(char* p_token)
{
	cout << "Validating Token Count: " << p_token << endl;

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
	cout << "Token Validation Result: " << result << endl;
	return result;
}


//static
unsigned int DefinitionValidator::is_valid_relative_address(char* p_token,
		ValidatorData* validator)
{
	cout << "Validating Relative Address: " << p_token << endl;

	unsigned int result = 0;
	static const unsigned int errorNumExpected = 1;

	locale loc;
	unsigned int token_length = strlen(p_token);
	//TODO: add a check if relative address too big / long?
	for(unsigned int i = 0; i < token_length; ++i)
	{
		if (!isdigit(p_token[i],loc))
		{
			cout << "ERROR: Invalid digit: " << p_token[i] << endl;
			result = errorNumExpected;
			//cout << "Address Validation Result: " << result << endl;
			return result;
		}
	}
	cout << "Address Validation Result: " << result << endl;
	return result;
}

bool DefinitionValidator::process(char* p_token) const
{
	cout << "DefinitionValidator processing: " << p_token << endl;
	/*
	if (p_token != 0)
	{
		if (DefinitionValidator::is_valid_relative_address(p_token))
		{
			cout << "Call Address handler()" << endl;
			return true;
		}
		else if (DefinitionValidator::is_valid_symbol(p_token))
		{
			cout << "Call Symbol handler()" << endl;
			return true;
		}
	}
	*/
	return false;
}

DefinitionValidator::ValidatorType::validator_enum DefinitionValidator::get_validator_enum() const
{
	cout << "DefinitionValidator ENUM: " << validatorType.DEFINITION << endl;
	return validatorType.DEFINITION;
}

void DefinitionValidator::set_offset(unsigned int offset)
{
	_offset = offset;
}

unsigned int DefinitionValidator::get_offset()
{
	return _offset;
}

void DefinitionValidator::append_symbol_and_offset_pair()
{
	_symbols_and_offsets.push_back(
			make_pair(SymbolValidator::get_symbol(),_offset));
}

unsigned int DefinitionValidator::get_symbols_count()
{
	return _symbols_and_offsets.size();
}
