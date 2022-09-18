#ifndef INCLUDED_PROGRAM_HEADER
#define INCLUDED_PROGRAM_HEADER

#include <base.h>
using namespace std;

class ProgramValidator: public BaseValidator
{
public:
	bool process() const;
	void set_instruction_type(char* instruction_type);
	char* get_instruction_type();
	void set_instruction_id(unsigned int instruction_id);
	unsigned int get_instruction_id();

private:
	char* _instruction_type;       // only 'R', 'E', 'I', or 'A' allowed
	unsigned int _instruction_id; //TODO add note about op/1000 and op mod 1000 studd
};

#endif
