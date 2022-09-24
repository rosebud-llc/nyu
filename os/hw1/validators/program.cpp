#include <program.h>
#include <iostream> // cout, endl
#include <string.h> // strlen
#include <locale>   // isalpha isdigit
#include <stdlib.h> // strtol, strtoul


//MUST BE INITIALIZED OUTSIDE CLASS BUT IN THIS CPP
static const char* program_types = "REIA";
static const set<char> valid_program_instruction_types(
		program_types,
		program_types+strlen(program_types));

//static
unsigned int ProgramValidator::is_valid_token_count(char* p_token, ModuleData& moduleData)
{
	//cout << "Validating Token Count: " << p_token 
	//	<< " with cumulative program instructions count: " 
	//	<< moduleData.get_cumulative_program_instructions() << endl;

	unsigned int result = 0;

	result = ProgramValidator::is_valid_number(p_token);
	if (result > 0)
	{
		return result;
	}
	
	static const unsigned int errorTooManyInstr = 7;
	static const unsigned int maxCumulativeProgramInstructions = 512;
	moduleData.set_cumulative_program_instructions(p_token);
	//cout << "New cumulative program instructions count: " 
	//	<< moduleData.get_cumulative_program_instructions() << endl; 
	if ( moduleData.get_cumulative_program_instructions() >
		maxCumulativeProgramInstructions)
	{
		result = errorTooManyInstr;
	}

	//cout << "Token Validation Result: " << result << endl;
	return result;
}

//Static
//TODO: does it matter if type is upper or lower case?
unsigned int ProgramValidator::is_valid_program_type(char* p_token)
{
	//cout << "Validating program type: " << p_token<< endl;

	unsigned int result = 0;
	static const unsigned int errorAddrExpected = 3;

	//TODO: should we do this null check everywhere? - maybe not since this is not a valid error and should be caught upstream
	if (p_token == 0)
	{
		cout << "ERROR: Token is empty: " << p_token << endl;
		result = 1;
		return result;
	}

	if(!valid_program_instruction_types.empty())
	{
		unsigned int token_length = strlen(p_token);
		if (token_length > 1)
		{
			cout << "ERROR: Invalid program type: " << p_token << ". Type name length too long: " << token_length << endl;
			result = errorAddrExpected;
		}
		// Should we do these p_token != 0 checks everywhere?
		else if (p_token != 0 &&
				valid_program_instruction_types.find(p_token[0]) !=
				valid_program_instruction_types.end())
		{
			result = 0;
		}
		else
		{
			cout << "ERROR: Invalid program type: " << p_token << endl;
			result = errorAddrExpected;
		}
	}
	// This should never happen - set should always be static initialized at top of this .cpp
	else
	{
		cout << "ERROR: set of valid program instruction types is empty!" << endl;
		result = errorAddrExpected;
	}
	//cout << "Program Type Valiation Result: " << result << endl;
	return result;
}

unsigned int ProgramValidator::is_valid_program_instruction(char* p_token)
{
	//cout << "Validating Program Instruction: " << p_token << endl;
	//TODO: NOTE this is only a PassTwo consideration, not a PassOne validation consideration
	// you need to validate that the instruction given can even be used w/ the program type
	// e.g. if given E 3000, but there are only 2 instructions in use list, then 3 is outbounds
	// check the lab1 doc to see how professor wants you to handle.

	unsigned int result = 0;
	if (p_token == 0)
	{
		cout << "ERROR: Token is empty: " << p_token << endl;
		result = 1;
		//cout << "Program Instruction Validation Result: " << result << endl;
		return result;
	}

	//TODO: need to add NULL check at start of this function similar to is_valid_symbol() or will throw error
	unsigned int token_length = strlen(p_token);

	/* TODO: disabled this check for test case input-19
	unsigned int required_integer_length = 4;
	cout << "token length: " << token_length << endl;
	if (token_length != required_integer_length)
	{
		cout << "ERROR: Instruction length does not equal required integer length." << endl;
		result = 1;
		//cout << "Program Instruction Validation Result: " << result << endl;
		return result;
	}
	*/

	locale loc;
	for(unsigned int i = 0; i < token_length; ++i)
	{
		if (!isdigit(p_token[i],loc))
		{
			cout << "ERROR: Invalid digit: " << p_token[i] << endl;
			result = 1;
			//cout << "Program Instruction Validation Result: " << result << endl;
			return result;
		}
	}
	/*
	long int instruction = strtol(p_token,NULL,10);
	if (instruction > 9999)
	{

	}
	*/
	//cout << "Program Instruction Validation Result: " << result << endl;
	return result;
}


bool ProgramValidator::process(char* p_token) const
{
	cout << "ProgramValidator processing: " << p_token << endl;
	return true;
}

ProgramValidator::ValidatorType::validator_enum ProgramValidator::get_validator_enum() const
{
	cout << "ProgramValidator ENUM: " << validatorType.PROGRAM << endl;
	return validatorType.PROGRAM;
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


