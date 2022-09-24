#ifndef INCLUDED_VALIDATOR_DATA_HEADER
#define INCLUDED_VALIDATOR_DATA_HEADER

#include <symbol_table/symbol_table.h> // key_strcmp
#include <module_data/module_data.h>
using namespace std;

struct ValidatorData
{
	char prevToken[32];           // Since max char for symbol is 16, double to 32 for buffer
	char currToken[32];           // Since max char for symbol is 16, double to 32 for buffer
	unsigned int tokenCount;      // How many tokens to validate
	unsigned int currBaseAddress; // Current base address
	unsigned int nextBaseAddress; // Next base address
	struct ValidatorType
	{
		static const unsigned int definition = 0;
		static const unsigned int use        = 1;
		static const unsigned int program    = 2;
	} type;
	unsigned int validatorType;
};

void initialize_validator_data(ValidatorData*,unsigned int);

void set_validator_count(char*,
		ValidatorData*,
		SymbolTable&,
		ModuleData&);

#endif
