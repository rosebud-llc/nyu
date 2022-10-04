#ifndef INCLUDED_SYMBOL_HEADER
#define INCLUDED_SYMBOL_HEADER

#include <base.h>
#include <string>
using namespace std;


class SymbolValidator: public BaseValidator
{
public:
	static unsigned int is_valid_symbol(char* p_token);
};

#endif
