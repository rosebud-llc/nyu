#include <program.h>
#include <iostream> // cout, endl

bool ProgramValidator::process() const
{
	cout << "ProgramValidator.process()" << endl;
	return true;
}

void ProgramValidator::set_instruction_type(char* instruction_type)
{
	_instruction_type = instruction_type;
}

char* ProgramValidator::get_instruction_type()
{
	return _instruction_type;
}

void ProgramValidator::set_instruction_id(unsigned int instruction_id)
{
	_instruction_id = instruction_id;
}

unsigned int ProgramValidator::get_instruction_id()
{
	return _instruction_id;
}


