#ifndef INCLUDED_USE_HEADER
#define INCLUDED_USE_HEADER

#include <symbol.h>
#include <vector>
#include <string>

using namespace std;

class UseValidator: public SymbolValidator
{
public:
	bool process(char* p_token) const;

	static unsigned int is_valid_token_count(char* p_token);

	ValidatorType::validator_enum get_validator_enum() const;
	void append_symbol(string& symbol);
	unsigned int get_symbols_count();

private:
	vector<string> _symbols;
};

#endif
