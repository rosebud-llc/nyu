#include <module_data.h>

#include <iostream> // cout, endl
#include <string.h> // strcpy
#include <stdlib.h> // strtol

/*
 *	Mutators
 */ 
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

void ModuleData::increment_memory_map_number()
{
	_memoryMapNumber++;
}

void ModuleData::insert_symbol_to_def_list(char* p_token)
{
	//TODO - double check that symbols added to _defList are deleted
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

void ModuleData::set_cumulative_program_instructions(char* p_token)
{
	long int l_count = strtol(p_token,NULL,10);
	unsigned int count = (unsigned int)l_count;
	_cumulativeProgramInstructions += count;
}

void ModuleData::insert_symbol_to_def_map(char* p_token, unsigned int moduleNumber)
{
	char* symbol = new char [sizeof(p_token)];
	if(p_token != NULL) strcpy(symbol,p_token);
	// Initialize symbol with module number it is first defined in and set usedFlag to false
	_defMap.insert(make_pair(symbol, 
		make_pair(moduleNumber,false)));
}

void ModuleData::set_symbol_to_used_in_def_map(char* p_token)
{
	
	map<char*, pair<unsigned int, bool>, key_strcmp >::iterator it 
		= _defMap.find(p_token);
	if(it == _defMap.end())
	{
		//TODO note this would throw an error for input-6, but here we treat as no-op
		//cout << "ERROR: unable to update symbol's usedFlag - does not exist in _defMap" << endl;
	}
	else
	{
		it->second.second = true;
	}
}

void ModuleData::clear_symbols_from_def_map()
{
	//TODO: delete elements from map
	/*unordered_set<pair<char*, pair<unsigned int, bool> > >::iterator it 
		= _defSet.begin();
	for(; it != _defSet.end(); ++it)
	{
		delete *it;
	}*/
	//TODO - is there a set 'erase' function?
}

void ModuleData::insert_symbol_to_use_list(char* p_token)
{
	char* symbol = new char [sizeof(p_token)];
	if(p_token != NULL) strcpy(symbol,p_token);
	// Initialize symbol with usedFlag set to false
	_useList.push_back(make_pair(symbol,false));
}

void ModuleData::clear_symbols_from_use_list()
{
	vector<pair<char*,bool> >::iterator it = _useList.begin();
        for(; it != _useList.end(); ++it)
        {
                delete it->first;
        }
        _useList.erase(_useList.begin(), _useList.end());	
}

/*
 *	Getters
 */ 
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

unsigned int ModuleData::get_memory_map_number()
{
	return _memoryMapNumber;
}

unsigned int ModuleData::get_cumulative_program_instructions()
{
	return _cumulativeProgramInstructions;
}

vector<char*> ModuleData::get_def_list()
{
	return _defList;
}

vector<pair<char*, bool> > ModuleData::get_use_list()
{
	return _useList;
}

void ModuleData::print_unused_symbols()
{
	bool prependNewLine = true;
	map<char*, pair<unsigned int,bool>, key_strcmp >::const_iterator c_it 
		= _defMap.begin();
	for(; c_it != _defMap.end(); ++c_it)
	{
		if (!c_it->second.second) 
		{
			if (prependNewLine)
			{
				cout << "\n";
				prependNewLine = false;
			}
			cout << "Warning: Module " << c_it->second.first << ": " 
				<< c_it->first << " was defined but never used" << endl;
		}
	}
}
