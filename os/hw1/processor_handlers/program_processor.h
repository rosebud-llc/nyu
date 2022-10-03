#ifndef INCLUDED_PROGRAM_PROCESSOR_HEADER
#define INCLUDED_PROGRAM_PROCESSOR_HEADER

//#include <module_data/module_data.h>
//#include <symbol_table/symbol_table.h>
// TODO - already includes module_data and validator_data
#include <validator_data/validator_data.h>
using namespace std;

unsigned int program_processor(
	char* p_token, 
	ValidatorData* validatorData,
	SymbolTable& symbolTable,
	ModuleData& moduleData);

#endif
