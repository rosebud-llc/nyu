#include <validator_data.h>

void initialize_validator_data(ValidatorData* validator,
		unsigned int validator_type)
{
	validator->validatorType   = validator_type;
	validator->tokenCount      = 0;
	validator->currBaseAddress = 0;
	validator->nextBaseAddress = 0;
}
