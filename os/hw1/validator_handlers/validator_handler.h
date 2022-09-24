#ifndef INCLUDED_VALIDATOR_HANDLER_HEADER
#define INCLUDED_VALIDATOR_HANDLER_HEADER

#include <module_data/module_data.h>
#include <validator_data/validator_data.h>
using namespace std;

unsigned int validator_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData,
		bool onlyEvaluateCount=false);

#endif
