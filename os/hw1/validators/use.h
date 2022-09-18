#ifndef INCLUDED_USE_HEADER
#define INCLUDED_USE_HEADER

#include <symbol.h>
#include <vector>
#include <string>

using namespace std;

class UseValidator: public SymbolValidator
{
public:
	bool process() const;
	void append_symbol(string& symbol);
	unsigned int get_symbols_count();

private:
	vector<string> _symbols;
};

#endif
