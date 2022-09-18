#include <definition.h>

#include <iostream> // cout, endl

bool DefinitionValidator::process() const
{
	cout << "DefinitionValidator.process()" << endl;
	return true;
}

void DefinitionValidator::set_offset(unsigned int offset)
{
	_offset = offset;
}

unsigned int DefinitionValidator::get_offset()
{
	return _offset;
}

void DefinitionValidator::append_symbol_and_offset_pair()
{
	_symbols_and_offsets.push_back(
			make_pair(SymbolValidator::get_symbol(),_offset));
}

unsigned int DefinitionValidator::get_symbols_count()
{
	return _symbols_and_offsets.size();
}
