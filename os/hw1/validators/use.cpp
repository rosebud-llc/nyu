#include <use.h>

#include <iostream> // cout, endl

bool UseValidator::process() const
{
	cout << "UseValidator.process()" << endl;
	return true;
}

void UseValidator::append_symbol(string& symbol)
{
	_symbols.push_back(symbol);
}

unsigned int UseValidator::get_symbols_count()
{
	return _symbols.size();
}
