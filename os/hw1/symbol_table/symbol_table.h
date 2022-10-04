#ifndef INCLUDED_SYMBOL_TABLE_HEADER
#define INCLUDED SYMBOL_TABLE_HEADER

#include <map>
#include <utility> // pair
#include <string.h> // strcmp, strcpy, strlen
using namespace std;


class SymbolTable
{
public:
	bool has_symbol(char* p_token);

	bool is_duplicate(char* p_token);

	unsigned int get_symbol_address(char* p_token);

	void insert_symbol_into_table(char* p_token);

	void update_symbol_relative_address(char* symbol, unsigned int address);

	void print_symbol_table();

	void delete_symbol_table_keys();

private:
	struct key_strcmp
	{
		bool operator()(char const *oldKey, char const *newKey) const
		{
			return strcmp(oldKey, newKey) < 0;
		}
	};

	map<char*, pair<unsigned int,bool>, key_strcmp > _symbolTable;
};

#endif
