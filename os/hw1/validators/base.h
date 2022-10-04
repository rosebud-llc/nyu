#ifndef INCLUDE_BASE_HEADER
#define INCLUDE_BASE_HEADER

using namespace std;

class BaseValidator
{
public:
	//TODO - delete destructor?
	virtual ~BaseValidator(){};

	static unsigned int is_valid_number(char* p_token);
	static bool is_valid_number_size(char* p_token,unsigned int maxTokenCount);
};

#endif
