#ifndef INCLUDED_DEFINITION_HEADER
#define INCLUDED_DEFINITION_HEADER

#include <symbol.h>
#include <map>
#include <utility>  // Pair
#include <string>
#include <vector>
#include <validator_data/validator_data.h>
using namespace std;

class DefinitionValidator: public SymbolValidator
{
public:
	static unsigned int is_valid_token_count(char* p_token);
	static unsigned int is_valid_relative_address(char* p_token,
			ValidatorData* validator);
};

#endif
