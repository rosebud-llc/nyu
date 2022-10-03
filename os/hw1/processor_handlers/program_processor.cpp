#include <program_processor.h>

#include <iostream>
#include <sstream> //stringstream
#include <string>
#include <stdlib.h> //strcmp
#include <string.h> //strcmp TODO which is it this include lib or the one above?
#include <iomanip> // setfill, setw


namespace
{
pair<unsigned int,unsigned int> get_opcode_and_operand(char* program_instruction)
{
	long int l_instruction
		= strtol(program_instruction,NULL,10);
	unsigned int instruction = (unsigned int)l_instruction;
	unsigned int opcode = instruction / 1000;
	unsigned int operand = instruction % 1000;
	pair<unsigned int, unsigned int> operation 
		= make_pair(opcode,operand);
	return operation;
}

string process_relative(stringstream& ss,
	unsigned int operand,
	ModuleData& moduleData)
{
	unsigned int absolute_address = 
		operand + moduleData.get_curr_base_address();
	if (absolute_address > moduleData.get_next_base_address())
	{	
		// Rule 9
		ss << setfill('0') << setw(3) << moduleData.get_curr_base_address()
			<< " Error: Relative address exceeds module size; zero used";
	}
	else
	{
		ss << setfill('0') << setw(3) << absolute_address;
	}
	return ss.str();
}

string process_external(stringstream& ss,
	unsigned int operand,
	SymbolTable& symbolTable,
	ModuleData& moduleData)
{
	vector<pair<char*,bool> > useList = moduleData.get_use_list();
	if (operand >= useList.size())
	{
		// Rule 6
		ss << setfill('0') << setw(3) << operand 
			<< " Error: External address exceeds length of uselist; treated as immediate";
	}
	else
	{	 
		if (!symbolTable.has_symbol(useList.at(operand).first))
		{
			// Rule 3
			ss << "000 Error: " << useList.at(operand).first << " is not defined; zero used"; 
		}
		else
		{
			unsigned int global_address 
				= symbolTable.get_symbol_address(useList.at(operand).first);
			ss << setfill('0') << setw(3) << global_address; 
			//TODO check that you're actually setting this to true otherwise you'll fail Rule 7 for module i.e. not all symbols in useList were used
			useList.at(operand).second = true;
			moduleData.set_symbol_to_used_in_def_map(
				useList.at(operand).first);
		}
	}
	return ss.str();
}

//TODO need clarification on nwhat absolute address / absolute zero / machine size instructions are here
string process_absolute(stringstream& ss,
	unsigned int operand,
	ModuleData& moduleData)
{
	unsigned int maxMachineSize = 512;
        if (operand > maxMachineSize)
        {
                // Rule 8
                ss << "000 Error: Absolute address exceeds machine size; zero used";
        }
        else
        {
                ss << setfill('0') << setw(3) << operand;
        }
        return ss.str();
}

// Pass in validator->prevtoken as program_type and p_token as program_instruction
// Return program instruction output
//TODO - you may need to check if program_type and program_instruction are NULL when new line is called but you haven't gotten the whole type/instruction pair?
string process_instruction(char* program_type,
        char* program_instruction,
        SymbolTable& symbolTable,
        ModuleData& moduleData)
{
	stringstream ss;
        pair<unsigned int, unsigned int> operation
                = get_opcode_and_operand(program_instruction);
        unsigned int opcode = operation.first;
        unsigned int operand = operation.second;
	
        if (opcode >= 10)
	{
		if (strcmp(program_type,"I") == 0)
		{
			// Rule 10
			return "9999 Error: Illegal immediate value; treated as 9999";
		}
		else
		{	
			// Rule 11
			return "9999 Error: Illegal opcode; treated as 9999";
		}
	}
	else
	{
		ss << opcode;	
	}

	if (strcmp(program_type,"R") == 0)
        {
                return process_relative(ss,
                        	operand,
                        	moduleData);
        }
        else if (strcmp(program_type,"E") == 0)
        {
                return process_external(ss,
                        operand,
                        symbolTable,
                        moduleData);
        }
        else if (strcmp(program_type,"I") == 0)
        {
		// Note: program_type "I" errors are handled when inspecting opcode above
                ss << operand;
		return ss.str();
        }
        else if (strcmp(program_type,"A") == 0)
        {
                return process_absolute(ss,
                        operand,
                        moduleData);
        }
        else
        {       
		return "ERROR: unrecognized instruction returning 9999 as default!";
        }
}

}; // end anonymous namespace

//TODO - pass ValidatorData because you need previous token to know what symbol is used for instruction
unsigned int program_processor(char* p_token,
	ValidatorData* validator,
	SymbolTable& symbolTable,
	ModuleData& moduleData)
{
	unsigned int result = 0;
	if (validator->tokenCount > 0) // this should never resolve to false
	{
		if (validator->tokenCount % 2 == 0)
		{
			// Process Program Type
			// - TODO: this may just be a no-op because prevToken in ValidatorData should have the symbol already
		}
		else
		{
			// Process Program Instruction given Program Type
			// - TODO: first, process the token to ensure number size/operand/operation are all correct or if error code is needed
			// - TODO: add R/E/I/A instruction handler here
			// - TODO: all Errors should be printed in-line here - no external info needed that you don't already have available in ModuleData or ValidatorData
			cout << setfill('0') << setw(3) << moduleData.get_memory_map_number() << ": " 
				<< process_instruction(validator->prevToken,
					p_token, 
					symbolTable,
					moduleData) 
				<< endl;
			moduleData.increment_memory_map_number(); 
		}
	}
	return result;
}
