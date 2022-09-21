#ifndef INCLUDED_VALIDATOR_DATA_HEADER
#define INCLUDED_VALIDATOR_DATA_HEADER

struct ValidatorData
{
	unsigned int tokenCount;      // How many tokens to validate
	unsigned int currBaseAddress; // Current base address
	unsigned int nextBaseAddress; // Next base address
	struct ValidatorType
	{
		static const unsigned int definition = 0;
		static const unsigned int use        = 1;
		static const unsigned int program    = 2;
	} type;
	unsigned int validatorType;
};

void initialize_validator_data(ValidatorData*,unsigned int);

#endif
