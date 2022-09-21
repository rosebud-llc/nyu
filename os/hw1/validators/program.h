#ifndef INCLUDED_PROGRAM_HEADER
#define INCLUDED_PROGRAM_HEADER

#include <base.h>
#include <set>
using namespace std;

class ProgramValidator: public BaseValidator
{

public:
	bool process(char* p_token) const;


	static unsigned int is_valid_token_count(char* p_token);
	static unsigned int is_valid_program_type(char* p_token);
	static unsigned int is_valid_program_instruction(char* p_token);

	ValidatorType::validator_enum get_validator_enum() const;
	void set_instruction_type(char* instruction_type);
	char* get_instruction_type();
	void set_instruction_id(unsigned int instruction_id);
	unsigned int get_instruction_id();

private:
	set<char*> _instruction_types;
	char* _instruction_type;       // only 'R', 'E', 'I', or 'A' allowed
	unsigned int _instruction_id; //TODO add note about op/1000 and op mod 1000 studd
};

#endif
