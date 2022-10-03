#include <definition_processor.h>

#include <iostream>

unsigned int definition_processor(char* p_token,
		ValidatorData* validator,
		ModuleData& moduleData)
{
	unsigned int result = 0;
	if (validator->tokenCount > 0) // this should never resolve to false
	{
		if (validator->tokenCount % 2 == 0)
		{
			// Definition Symbol
			// - add symbol to ModuleData's _defSet
			// - set _defSet's moduleNumber to _moduleNumber
			// - set _defSet's usedFlag to false
			moduleData.insert_symbol_to_def_map(
				p_token,
				moduleData.get_module_number());
			return result;
			
		}
		else
		{
			// Definition Relative Addresss 
			// - no processing required (i.e. no-op)
			return result;
		}
	}
	return result;
}
