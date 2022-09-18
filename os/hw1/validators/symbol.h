#ifndef INCLUDED_SYMBOL_HEADER
#define INCLUDED_SYMBOL_HEADER

#include <base.h>
#include <string>
using namespace std;

//TODO: change strings to char* to enforce char* _symbol[15]
class SymbolValidator: public BaseValidator
{
public:
	void set_symbol(string& symbol);
	string get_symbol();

private:
	string _symbol;             // max. 16 char with regex [a-Z][a-Z0-9]* enforced by setter

};

#endif
