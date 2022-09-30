#include <validator_data.h>

#include <string.h> // strcpy
#include <stdlib.h> // strtol
#include <iostream>

namespace
{

void set_relative_address(char* symbol, SymbolTable& symbolTable, ModuleData& moduleData)
{
	//TODO add check here if symbolTable.is_symbol_address_locked(symbol) and do NOT update address if it has already been set upon first instance (see rule 5)
	// NOTE - you don't need to do that - we exclude definitions that are duplicates from the ModuleData _defList, so you'll never erroneously update symbolTable symbol's address
	if (symbolTable.has_symbol(symbol))
	{
		unsigned int relativeAddress =
				symbolTable.get_symbol_address(symbol);
		unsigned int maxRelativeAddress =
				moduleData.get_next_base_address() - moduleData.get_curr_base_address(); // TODO 0-based counting so subtract 1?
		cout << "Symbol's Relative   Address(" << relativeAddress << ")" << endl;
		cout << "Max      Relative   Address(" << maxRelativeAddress << ")" << endl;

		if (relativeAddress > maxRelativeAddress)
		{
			//TODO - we subtract 1 from maxRelativeAddress to make input-10 work for warning.
			// The symbolTable is correct tho without making any adjustments.  Why?
			cout << "Warning: Module " << moduleData.get_module_number() << ": "
					<< symbol << " too big " << relativeAddress
					<< " (max=" << maxRelativeAddress-1 << ") assume zero relative" << endl;

			symbolTable.update_symbol_relative_address(symbol,
					moduleData.get_curr_base_address());
		}
		else
		{
			unsigned int absoluteAddress =
					moduleData.get_curr_base_address() + relativeAddress;
			symbolTable.update_symbol_relative_address(symbol,
					absoluteAddress);
		}
	}
	// This should not happen - unless it's a test case covered in the paper, must read
	else
	{
		cout << "ERROR: Unable to find Symbol that requires address update!!!" << symbol << endl;
	}
}
} // end anonymous namespace

void initialize_validator_data(ValidatorData* validator,
		unsigned int validator_type)
{
	strcpy(validator->prevToken, "");
	strcpy(validator->currToken, "");
	validator->tokenCount      = 0;
	validator->currBaseAddress = 0;
	validator->nextBaseAddress = 0;
	validator->validatorType   = validator_type;
}

void set_validator_count(char* p_token,
		ValidatorData* validator,
		SymbolTable& symbolTable,
		ModuleData& moduleData)
{
	cout << "Given ValitdatorType(" << validator->validatorType << ") Count: " << p_token << endl;
	long int l_count = strtol(p_token,NULL,10);
	unsigned int count = (unsigned int)l_count;

	//TODO: if def_validator or prog_validator, count needs to be multiplied by 2 since you're dealing with paired (S,R) and (type, instr) entries to process
	if (validator->validatorType == 0 || validator->validatorType == 2)
	{
		if (validator->validatorType == 0)
		{
			moduleData.increment_module_number();
		}
		if (validator->validatorType == 2)
		{
			moduleData.set_curr_base_address(moduleData.get_next_base_address());
			moduleData.set_next_base_address(count);
			//cout << "Current Module Base Address(" << moduleData.get_curr_base_address() << ")" << endl;
			//cout << "Next    Module Base Address(" << moduleData.get_next_base_address() << ")" << endl;

			vector<char*> defList = moduleData.get_def_list();
			vector<char*>::const_iterator c_it = defList.begin();
			for(; c_it != defList.end(); ++c_it)
			{
				//cout << "SYMBOL: " << *c_it << endl;
				set_relative_address(*c_it, symbolTable, moduleData);
			}
			moduleData.clear_symbols_from_def_list();
		}
		count = count * 2;
	}
	validator->tokenCount = (count >= 0) ? count : 0; // TODO: Set count to 0 if count < 0 ? And Skip?
	cout << "Set ValidatorType(" << validator->validatorType << ") Count: " << validator->tokenCount << endl;
}
