#ifndef INCLUDED_DEFINITION_HEADER
#define INCLUDED_DEFINITION_HEADER

#include <symbol.h>
#include <map>
#include <utility>  // Pair
#include <string>
#include <vector>
#include <validator_data/validator_data.h>
using namespace std;

class DefinitionValidator: public SymbolValidator
{
public:
	bool process(char* p_token) const;

	static unsigned int is_valid_token_count(char* p_token);
	static unsigned int is_valid_relative_address(char* p_token,
			ValidatorData* validator);

	ValidatorType::validator_enum get_validator_enum() const;
	void set_offset(unsigned int offset);
	unsigned int get_offset();
	void append_symbol_and_offset_pair();
	unsigned int get_symbols_count();

private:
	unsigned int _offset;       // 0-based index
	vector<pair<string, unsigned int> > _symbols_and_offsets;

};


#endif
