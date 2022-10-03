#ifndef INCLUDED_DEFINITION_PROCESSOR_HEADER
#define INCLUDED_DEFINITION_PROCESSOR_HEADER

#include <validator_data/validator_data.h>
using namespace std;

unsigned int definition_processor(char* p_token,
		ValidatorData* validator,
		ModuleData& moduleData);

#endif
