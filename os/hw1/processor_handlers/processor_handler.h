#ifndef INCLUDED_PROCESSOR_HANDLER_HEADER
#define INCLUDED_PROCESSOR_HANDLER_HEADER

//#include <module_data/module_data.h>
//#include <symbol_table/symbol_table.h>
//TODO - this'll get renamed to something_data
// - already includes ModuleData and SymbolTable headers
#include <validator_data/validator_data.h>
using namespace std;

unsigned int processor_handler(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData);

#endif
