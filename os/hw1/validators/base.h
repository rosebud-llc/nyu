#ifndef INCLUDE_BASE_HEADER
#define INCLUDE_BASE_HEADER

using namespace std;

class BaseValidator
{
public:
	virtual ~BaseValidator(){};

	virtual bool process(char* p_token) const = 0;

	static unsigned int is_valid_number(char* p_token);
	static bool is_valid_number_size(char* p_token,unsigned int maxTokenCount);

	struct ValidatorType
	{
		//TODO: Add BASE and SYMBOL for consistency;
		enum validator_enum {DEFINITION,USE,PROGRAM};
	} validatorType;
	virtual ValidatorType::validator_enum get_validator_enum() const = 0;

private:
	unsigned int _count;

};

#endif
