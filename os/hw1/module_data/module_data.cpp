#include <module_data.h>

#include <string.h> // strcpy

void ModuleData::increment_module_number()
{
	_moduleNumber++;
}

void ModuleData::set_curr_base_address(unsigned int baseAddress)
{
	_currBaseAddress = baseAddress;
}

void ModuleData::set_next_base_address(unsigned int baseAddress)
{
	_nextBaseAddress += baseAddress;
}

void ModuleData::insert_symbol_to_def_list(char* p_token)
{
	char* symbol = new char [sizeof(p_token)];
	if(p_token != NULL) strcpy(symbol,p_token);
	_defList.push_back(symbol);
}

void ModuleData::clear_symbols_from_def_list()
{
	vector<char*>::iterator it = _defList.begin();
	for(; it != _defList.end(); ++it)
	{
		delete *it;
	}
	_defList.erase(_defList.begin(), _defList.end());
}

unsigned int ModuleData::get_module_number()
{
	return _moduleNumber;
}

unsigned int ModuleData::get_curr_base_address()
{
	return _currBaseAddress;
}

unsigned int ModuleData::get_next_base_address()
{
	return _nextBaseAddress;
}

vector<char*> ModuleData::get_def_list()
{
	return _defList;
}
