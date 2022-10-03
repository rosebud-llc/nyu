#ifndef INCLUDED_MODULE_DATA_HEADER
#define INCLUDED_MODULE_DATA_HEADER

#include <vector>
#include <map>
#include <utility> // pair
using namespace std;

class ModuleData
{
public:

	ModuleData():
		_moduleNumber(0),
		_currBaseAddress(0),
		_nextBaseAddress(0),
		_memoryMapNumber(0),
		_cumulativeProgramInstructions(0) {};

	// mutators for unsigned int private member variables
	void increment_module_number();
	void set_curr_base_address(unsigned int);
	void set_next_base_address(unsigned int);
	void increment_memory_map_number();
	void set_cumulative_program_instructions(char* p_token);
	// _defList mutators
	void insert_symbol_to_def_list(char* p_token);
	void clear_symbols_from_def_list();
	// _defMap mutators
	void insert_symbol_to_def_map(char* p_token, unsigned int moduleNumber);
	void set_symbol_to_used_in_def_map(char* p_token);
	void clear_symbols_from_def_map();
	// _useList mutator
	void insert_symbol_to_use_list(char* p_token);
	void clear_symbols_from_use_list();

	// getters for unsigned int private member variables
	unsigned int get_module_number();
	unsigned int get_curr_base_address();
	unsigned int get_next_base_address();
	unsigned int get_memory_map_number();
	unsigned int get_cumulative_program_instructions();
	// _defList getter
	vector<char*> get_def_list();
	// _defMap getter
	void print_unused_symbols();
	// _useList getter
	vector<pair<char*, bool> > get_use_list();
	
private:
	struct key_strcmp
        {
                bool operator()(char const *oldKey, char const *newKey) const
                {
                        return strcmp(oldKey, newKey) < 0;
                }
        };

	unsigned int _moduleNumber;
	unsigned int _currBaseAddress;
	unsigned int _nextBaseAddress;
	unsigned int _memoryMapNumber; // increment for each program instruction processed in pass two
	unsigned int _cumulativeProgramInstructions; // cumulative number of instructions for *all* modules processed
	
	/* _defList use case:
	 	- push_back each defined symbol in module. 
	   	- at end of module, iterate over vector and insert each symbol into symbol table
	   	- _defList is cleared before processing next module
	*/
	vector<char*> _defList;
	
	/* _defMap use case
		- insert each defined symbol ensuring for given symbol, only first instance is added
		- set symbol's Module number and whether or not symbol was ever used at least once in Program
		- at end of Program, if symbol never used, print warning Rule 4
	*/
	map<char*, pair<unsigned int,bool>, key_strcmp > _defMap;
	
	/* _useList use case
		- push_back each 'used' symbol for given module
		- during execution of program instructions in a given, mark if symbol used
		- at end of module, if symbol unused, print warning Rule 7
	*/
	vector<pair<char*, bool> > _useList;
};

#endif
