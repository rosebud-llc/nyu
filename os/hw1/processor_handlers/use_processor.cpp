#include <use_processor.h>

#include <iostream>


unsigned int use_processor(char* p_token,
		ModuleData& moduleData)
{
	unsigned int result = 0;
	// Use List Symbols
	// - add symbol to _useList vector
	// - set usedFlag to false	
	moduleData.insert_symbol_to_use_list(p_token);
	return result;
}
