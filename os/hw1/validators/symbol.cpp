#include <symbol.h>

void SymbolValidator::set_symbol(string& symbol)
{
	_symbol = symbol;
}

string SymbolValidator::get_symbol()
{
	return _symbol;
}
