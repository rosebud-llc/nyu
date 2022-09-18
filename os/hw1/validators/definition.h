#ifndef INCLUDED_DEFINITION_HEADER
#define INCLUDED_DEFINITION_HEADER

#include <symbol.h>
#include <utility>  // Pair
#include <string>
#include <vector>
using namespace std;

class DefinitionValidator: public SymbolValidator
{
public:
	bool process() const;
	void set_offset(unsigned int offset);
	unsigned int get_offset();
	void append_symbol_and_offset_pair();
	unsigned int get_symbols_count();

private:
	unsigned int _offset;       // 0-based index
	vector<pair<string, unsigned int> > _symbols_and_offsets;
};


#endif
