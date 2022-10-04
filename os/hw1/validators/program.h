#ifndef INCLUDED_PROGRAM_HEADER
#define INCLUDED_PROGRAM_HEADER

#include <base.h>
#include <set>
#include <module_data/module_data.h>
using namespace std;

class ProgramValidator: public BaseValidator
{

public:
	static unsigned int is_valid_token_count(char* p_token, ModuleData& moduleData);
	static unsigned int is_valid_program_type(char* p_token);
	static unsigned int is_valid_program_instruction(char* p_token);
};

#endif
