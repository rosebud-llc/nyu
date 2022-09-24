#ifndef INCLUDED_DEFINITION_HANDLER_HEADER
#define INCLUDED_DEFINITION_HANDLER_HEADER

#include <validator_data/validator_data.h>
using namespace std;

unsigned int definition_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData,
		bool onlyEvaluateCount=false);

#endif
