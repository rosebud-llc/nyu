#ifndef INCLUDED_USE_HEADER
#define INCLUDED_USE_HEADER

#include <symbol.h>
#include <vector>
#include <string>

using namespace std;

class UseValidator: public SymbolValidator
{
public:
	static unsigned int is_valid_token_count(char* p_token);

};

#endif
