#include <symbol_table.h>

// TODO is this needed? can we use soemthing from string.h instead? which is in header file
#include <stdlib.h> // strtoul
#include <string>
#include <iostream>
/*
void SymbolTable::load_symbol_table_2()
{
	char* t1 = "Hello";
	SymbolInfo test1;
	test1._address = 1;
	test1._isDuplicated = true;
	test1._isAddressLocked = false;

	char* t2 = "World!";
	SymbolInfo test2;
	test2._address = 2;
	test2._isDuplicated = true;
	test2._isAddressLocked = true;

	_symbolTable2.insert(make_pair(t1,test1));
	_symbolTable2.insert(make_pair(t2,test2));

	int count = 0;
	map<char*, SymbolInfo, key_strcmp>::iterator it = _symbolTable2.begin();
	for(; it != _symbolTable2.end(); ++it)
	{
		cout << "Test " << count << ": " << it->first << it->second._address << it->second._isDuplicated << it->second._isAddressLocked << endl;
		count++;
	}
}
*/
void SymbolTable::add_symbol_info(char* symbol, unsigned int address, bool isDuplicated, bool isAddressLocked)
{
	cout << "Adding new symbol: " << symbol << endl;
	SymbolInfo* symbolInfo = new SymbolInfo;
	symbolInfo->_address = address;
	symbolInfo->_isDuplicated = isDuplicated;
	symbolInfo->_isAddressLocked = isAddressLocked;
	_symbolTable2.insert(make_pair(symbol,symbolInfo));
	cout << "Symbol added!" << endl;
}

void SymbolTable::print_symbols()
{
	map<char*, SymbolInfo*, key_strcmp >::iterator map_itr =
			_symbolTable2.begin();
	for(; map_itr != _symbolTable2.end(); ++map_itr)
	{
		cout << "Symbol: " << map_itr->first
				<< " Address: " << map_itr->second->_address
				<< " isDuplicated: " << map_itr->second->_isDuplicated
				<< " isAddressLocked: " << map_itr->second->_isAddressLocked
				<< endl;
	}
}

void SymbolTable::delete_symbols()
{
	map<char*, SymbolInfo*, key_strcmp >::iterator map_itr =
			_symbolTable2.begin();
	for(; map_itr != _symbolTable2.end(); ++map_itr)
	{
		delete map_itr->second;
	}
}

bool SymbolTable::has_symbol(char* p_token)
{
	map<char*, pair<unsigned int, bool>, key_strcmp >::iterator it = _symbolTable.find(p_token);
	return it != _symbolTable.end();
}

bool SymbolTable::is_duplicate(char* p_token)
{
	map<char*, pair<unsigned int, bool>, key_strcmp >::iterator it = _symbolTable.find(p_token);
	if (it != _symbolTable.end())
	{
		return it->second.second;
	}
	// This should never happen
	else
	{
		//cout << "ERROR: Symbol not in table: " << p_token << ". Can't determine if isDuplicate" << endl;
	}
	return false;
}

unsigned int SymbolTable::get_symbol_address(char* p_token)
{
	map<char*, pair<unsigned int, bool>, key_strcmp >::iterator it =
			_symbolTable.find(p_token);
		if( it != _symbolTable.end() )
		{
			return it->second.first;
		}
		else
		{
			//cout << "ERROR: Symbol not found in table. Returning 0 as default." << endl;
			return 0;
		}
}

// TODO: this should only ever be called when running DefinitionValidator, not UseValidator
void SymbolTable::insert_symbol_into_table(char* p_token)
{
	map<char*, pair<unsigned int,bool>, key_strcmp>::iterator it =
			_symbolTable.find(p_token);
	if (it == _symbolTable.end())
	{
		// Initialize symbol with relative_address=0 and is_duplicate=false
		//cout << "Adding new symbol " << p_token << " to symbolTable" << endl;

		// Key is read-only and you can't 'delete' later to free memory
		char* key = new char [strlen(p_token)];
		strcpy(key,p_token);
		_symbolTable.insert(make_pair(key,
				make_pair(-1,false))); // TODO initialize address as -1 so you know whether or not it's been set?
	}
	else
	{
		//cout << "FOUND MATCH: " << it->first << ". Marking symbol " << p_token << " as duplicate in symbolTable" << endl;
		// Mark Symbol as duplicate
		it->second.second = true;
	}
	//cout << "PRINT MAP CONTENTS" << endl;
	map<char*, pair<unsigned int,bool>, key_strcmp >::iterator itr = _symbolTable.begin();
	for(; itr != _symbolTable.end(); ++itr)
	{
		//cout << "\tKey: " << itr->first << " Value: (Rel_Addr: " << itr->second.first << ", isDuplicate: " << itr->second.second << ")" << endl;
	}
}

void SymbolTable::update_symbol_relative_address(char* symbol, unsigned int address)
{
	map<char*, pair<unsigned int,bool>, key_strcmp >::iterator it =
				_symbolTable.find(symbol);
		if (it == _symbolTable.end())
		{
			cout << "ERROR: Failed to update realtive address because this symbol does not exist: " << symbol << endl;
		}
		else
		{
			//cout << "Updating address for symbol " << symbol << " from " << it->second.first << " to " << address << endl;
			it->second.first = address;
		}
}

void SymbolTable::print_symbol_table()
{
	map<char*, pair<unsigned int,bool>, key_strcmp >::iterator map_itr =
			_symbolTable.begin();
	cout << "Symbol Table" << endl;
	for(; map_itr != _symbolTable.end(); ++map_itr)
	{
		cout << map_itr->first << "=" << map_itr->second.first;
		if (map_itr->second.second)
		{
			cout << " Error: This variable is multiple times defined; first value used";
		}
		cout << endl;
	}
}

//TODO: need to fix how we add 'new' char* and then 'delete' - it's not being done correctly and can create segfault
void SymbolTable::delete_symbol_table_keys()
{
	map<char*, pair<unsigned int,bool>, key_strcmp >::iterator map_itr =
			_symbolTable.begin();
	for(; map_itr != _symbolTable.end(); ++map_itr)
	{
		delete map_itr->first;
	}
	//cout << "symbol table size after delete: " << _symbolTable.size() << endl;
}

