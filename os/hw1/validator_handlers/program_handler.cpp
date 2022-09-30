#include <program_handler.h>

#include <iostream>
#include <validators/program.h>    // is_valid_program_type

unsigned int program_handler(char* p_token,
	unsigned int count,
	ModuleData& moduleData, 
	bool onlyEvaluateCount)
{
	if (onlyEvaluateCount)
	{
		return ProgramValidator::is_valid_token_count(p_token,moduleData);
	}

	unsigned int result = 0;
	if (count > 0) // this should never resolve to false
	{
		if (count % 2 == 0)
		{
			result = ProgramValidator::is_valid_program_type(p_token);
			cout << "is_valid_program_type: " <<  result << endl;
		}
		else
		{
			result = ProgramValidator::is_valid_program_instruction(p_token);
			cout << "is_valid_program_instruction: " << result << endl;
		}
	}
	return result;
}
