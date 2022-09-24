#ifndef INCLUDED_PROGRAM_HANDLER_HEADER
#define INCLUDED_PROGRAM_HANDLER_HEADER

#include <module_data/module_data.h>
using namespace std;

unsigned int program_handler(
	char* p_token, 
	unsigned int count, 
	ModuleData& moduleData,
	bool onlyEvaluateCount=false);

#endif
