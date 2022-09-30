#ifndef INCLUDED_MODULE_DATA_HEADER
#define INCLUDED_MODULE_DATA_HEADER

#include <vector>
using namespace std;

class ModuleData
{
public:

	ModuleData():
		_moduleNumber(0),
		_currBaseAddress(0),
		_nextBaseAddress(0),
		_cumulativeProgramInstructions(0) {};

	void increment_module_number();
	void set_curr_base_address(unsigned int);
	void set_next_base_address(unsigned int);
	void insert_symbol_to_def_list(char* p_token);
	void clear_symbols_from_def_list();
	void set_cumulative_program_instructions(char* p_token);

	unsigned int get_module_number();
	unsigned int get_curr_base_address();
	unsigned int get_next_base_address();
	vector<char*> get_def_list();
	//vector<char*> get_use_list();
	unsigned int get_cumulative_program_instructions();

private:
	unsigned int _moduleNumber;
	unsigned int _currBaseAddress;
	unsigned int _nextBaseAddress;
	vector<char*> _defList;
	vector<char*> _useList;
	unsigned int _cumulativeProgramInstructions; // cumulative number of instructions for *all* modules processed
};

#endif