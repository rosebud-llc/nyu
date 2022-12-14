#include <tokenizer.h>

#include <io_handlers/log_io.h> // getLogPrefix
#include <ctype.h>    // isspace
#include <string.h> // strtok
#include <stdlib.h> // strtol, EXIT_FAILURE
#include <iostream> // cout, endl
#include <sstream>  // stringstream, str
#include <fstream>  // getline, is_open, close
#include <map>

#include <module_data/module_data.h> // Class ModuleData
#include <validator_data/validator_data.h> // key_strcmp
#include <validator_handlers/validator_handler.h>
#include <validator_queue/validator_queue.h> // initialize_validator_queue, delete_validator_queue, reorder_validator_queue
#include <processor_handlers/processor_handler.h>
using namespace std;


void exit_on_parse_error(unsigned int errorCode,
		unsigned int lineNum, unsigned int lineOffset)
{
	static const char* errorString[] = {
			"SUCCESS",                  // (0) No error
			"NUM_EXPECTED",            // (1) Number expected, anything >= 2^30 is not a number either
			"SYM_EXPECTED",            // (2) Symbol expected
			"ADDR_EXPECTED",           // (3) Addressing expected which is A/E/I/R
			"SYM_TOO_LONG",            // (4) Symbolg Name is too long
			"TOO_MANY_DEF_IN_MODULE",  // (5) > 16
			"TOO_MANY_USE_IN_MODULE",  // (6) > 16
			"TOO_MANY_INSTR",          // (7) total num_instr exceeds memory size (512)
	};
	//TODO: need to define what constitutes a syntax error vs. poarsing error because only synatx error should cause program to stop altogether
	//TODO: actually looking at out-10-19 examples it looks like all of these are syntax errors that EXIT on failure
	if (errorCode > 0)
	{   /*
		for(unsigned int i = 0; i<sizeof(errorString); ++i)
		{
			cout << "errorCode: " << errorCode << " | errorString: " << errorString[i] << endl;
		}*/
		cout << "Parse Error line " << lineNum << " offset " << lineOffset << ": " << errorString[errorCode] << endl;
		//TODO using EXIT_SUCCESS here to avoid extra print line of EXIT_FAILURE that indicates an actual error occured
		exit(EXIT_SUCCESS);
	}
}

void set_string_start_from_matching_token(string& line, char* p_token, unsigned int& tokenOffset)
{
	//cout << "Old String: " << line << endl;
	if (p_token != 0)
	{
		//cout << "String to find (p_token): " << p_token << endl;
		stringstream ss;
		bool stopCountingTabs = false;
		string::iterator s_itr = line.begin();
		for (; s_itr != line.end(); ++s_itr)
		{
			// Increment tokenOffset by number of tabs processed
			if ( !isalnum(*s_itr) && !ispunct(*s_itr) && !stopCountingTabs)
			{
				//cout << "String isempty/isspace && doNotStopCountingTabs... tokenOffset(+1)" << endl;
				tokenOffset++;
			}
			// Stop counting tabs once matching token found
			// TODO does this work comparing string to dereferenced c-string?
			else if ( (isalnum(*s_itr) || ispunct(*s_itr)) && !stopCountingTabs)
			{
				//cout << "String isalnum/ispunct ";
				if (*s_itr == *p_token)
				{
					//cout << "and string equals p_token... tokenOffset(+1)" << endl; // << strlen(p_token) << ")... and stop counting" << endl;
					tokenOffset++; //+= strlen(p_token);
					stopCountingTabs = true;
				}
				else
				{
					//cout << " and doNotStopCountingTabs... tokenOffset(+1)" << endl;
					tokenOffset++;
				}
			}
			// When done counting tabs, concatenate substring starting from token
			else if (stopCountingTabs)
			{
				//cout << "Add string (" << *s_itr << ") to stringstream... no tokenOffset increment" << endl;
				ss << *s_itr;
			}
		}
		// Reset string to substring starting from token
		line = ss.str();
		//cout << "New String: " << line << endl;
	}
}

char* convert_string_to_cstring(string& line)
{
	char* p_cstring = new char [line.length()+1];
	strcpy(p_cstring,line.c_str());
	return p_cstring;
}

char* nextToken(char* p_token, unsigned int& tokenOffset)
{
	static const char* delims = " \t\n";
	return strtok(p_token,delims);
}

void tokenizerPassOne(string& line,
		unsigned int lineNumber,
		unsigned int& tokenOffset,
		queue<ValidatorData*>& validators,
		SymbolTable& symbolTable,
		ModuleData& moduleData)
{
	// Next Token
	// DO NOT UPDATE PREV TOKEN HERE like you do in the other nextToken calls
	string orig_line = line;
	char* p_cstring = convert_string_to_cstring(line);
	char* p_token = nextToken(p_cstring,tokenOffset);

	ValidatorData* validator = validators.front();
	while (p_token != 0)
	{
		// Start of linker file || ready for next validator || new line has zero items to read
		if (validator->tokenCount == 0)
		{
			// First, validate count
			//cout << "Validate Count: " << p_token << " because validator->tokenCount == " << validator->tokenCount << endl;
			unsigned int is_valid_count = validator_handler(p_token, validator, symbolTable, moduleData, true);
			//cout << "Is Valid Count: " << is_valid_count << endl;
			if (is_valid_count > 0)
			{
				// Increment tokenOffset - failed to validate count
				tokenOffset++;
				exit_on_parse_error(is_valid_count,lineNumber,tokenOffset);
			}
			// Then set count
			set_validator_count(p_token,validator,symbolTable,moduleData);
			//If count STILL zero even after parsing token count, then move to next validator
			if (validator->tokenCount == 0)
			{
				reorder_validator_queue(validators);
				validator = validators.front();
			}
			// Next Token
			if(p_token != NULL) strcpy(validator->prevToken,p_token); // update prevToken
			p_token = nextToken(NULL, tokenOffset);
			if(p_token != NULL)
			{	 
				strcpy(validator->currToken,p_token); // update currToken
			}
			else // token is NULL, exit from tokenizer() and getline on next iteration to process
			{
				// Increment tokenOffset to account for count which was validated
				set_string_start_from_matching_token(orig_line,validator->prevToken,tokenOffset);
				delete[] p_cstring;
				return;
			}
		}
		// Only enter this while loop when you actually have something to process (i.e. count is > 0)
		while(validator->tokenCount > 0) // NOTE YOU REMOVED P_TOKEN NULL CHECK FROM HERE ON 09/23 DUE TO input-13 TEST FAIL
		{
			unsigned int is_valid_syntax = validator_handler(p_token, validator, symbolTable, moduleData);
			//cout << "Is Valid Syntax: " << is_valid_syntax << endl;
			// Need to calculate tokenOffset before printing Error if syntax not valid
			set_string_start_from_matching_token(orig_line,p_token,tokenOffset);
			if (is_valid_syntax > 0)
			{
				exit_on_parse_error(is_valid_syntax,lineNumber,tokenOffset);
			}

			// Next Token
			if(p_token != NULL) strcpy(validator->prevToken,p_token); // update prevToken
			p_token = nextToken(NULL, tokenOffset);
			if(p_token != NULL)
			{
				 strcpy(validator->currToken,p_token); // update currToken
			
			}
			// Case where Definition Count set to 0 because there's nothing to process, you don't want to decrement  to negative value.. altho not posisble if this is unsigned int, but better to check and be sure
			if (validator->tokenCount > 0)
			{     
				//cout << "Decrement ValidatorType(" << validator->validatorType << ") from " << validator->tokenCount;
				validator->tokenCount--;
				//cout << " to " << validator->tokenCount << endl;
			}
			//cout << "VALIDATOR COUNT: " << validator->tokenCount << endl;
			if (validator->tokenCount == 0)
			{
				reorder_validator_queue(validators);
				validator = validators.front();
				//cout << "QUEUE REORDERED - FINISHED PROCESSING" << endl;
				break;
			}
			if(p_token == NULL) // this is the same check as when you return during the set count loop above.
			// token is NULL, exist from tokenizer() and getline on next iteration to process 
			{
				//cout << "EXIT tokenizer because next token is NULL" << endl;
				delete[] p_cstring;
				return;
			}
		}
	}
	// Deallocate mem
	delete[] p_cstring;
	return;
}

void tokenizerPassTwo(string& line,
                unsigned int lineNumber,
                unsigned int& tokenOffset,
                queue<ValidatorData*>& validators,
                SymbolTable& symbolTable,
                ModuleData& moduleData)
{
        string orig_line = line;
        char* p_cstring = convert_string_to_cstring(line);
        char* p_token = nextToken(p_cstring,tokenOffset);

        ValidatorData* validator = validators.front();
        while (p_token != 0)
        {
                // Start of linker file || ready for next validator || new line has zero items to read
                if (validator->tokenCount == 0)
                {       
			// First, validate count
			// TODO - change this to processor_handler 
                        unsigned int is_valid_count = validator_handler(p_token, validator, symbolTable, moduleData, true);
                        // No error checking required to EXIT since this is passTwo
			if (is_valid_count > 0)
                        {       
                                exit_on_parse_error(is_valid_count,lineNumber,tokenOffset);
                        }
                        // Then set count
                        set_validator_count(p_token,validator,symbolTable,moduleData);
                        if (validator->tokenCount == 0)
                        {       
                                reorder_validator_queue(validators);
                                validator = validators.front();
                        }
                        // Next Token
                        if(p_token != NULL) strcpy(validator->prevToken,p_token); // update prevToken
                        p_token = nextToken(NULL, tokenOffset);
                        set_string_start_from_matching_token(orig_line, p_token, tokenOffset);
                        if(p_token != NULL)
                        {        
                                strcpy(validator->currToken,p_token); // update currToken
                        }
                        else // token is NULL, exit from tokenizer() and getline on next iteration to process
                        {       
                                delete[] p_cstring;
                                return;
                        }
                        if(p_token == NULL) cout << "Token is null!" << endl;
                }
                while(validator->tokenCount > 0)
                {       
                        unsigned int is_valid_processor = processor_handler(p_token, validator, symbolTable, moduleData);
                        if (is_valid_processor > 0)
                        {       
                                exit_on_parse_error(is_valid_processor,lineNumber,tokenOffset);
                        }
                        
                        // Next Token
                        if(p_token != NULL) strcpy(validator->prevToken,p_token); // update prevToken
                        p_token = nextToken(NULL, tokenOffset);
                        set_string_start_from_matching_token(orig_line, p_token, tokenOffset);
                        if(p_token != NULL)
                        {        
                                 strcpy(validator->currToken,p_token); // update currToken
                        
                        }    
                        if (validator->tokenCount > 0)
                        {
                                validator->tokenCount--;
                        }
                        if (validator->tokenCount == 0)
                        {       
				// Print unused symbols from Module when finished processing all instructions
                                if (validator->validatorType == 2)
				{
					moduleData.print_unused_symbols_from_module();
				}
				reorder_validator_queue(validators);
                                validator = validators.front();
                                break;
                        }
                        if(p_token == NULL) // this is the same check as when you return during the set count loop above.
                        {       
                                delete[] p_cstring;
                                return;
                        }
                }
        }
        // Deallocate mem
        delete[] p_cstring;
        return;
}

void processFileStream(const char* input_file_name)
{
	SymbolTable symbolTable;
	
	// Pass One
	ifstream input_file_stream1;
	input_file_stream1.open(input_file_name);
	if (input_file_stream1.is_open())
	{
		string line;
		unsigned int lineNumber = 0;
		unsigned int tokenOffset = 0;
		queue<ValidatorData*> validators = initialize_validator_queue();
		ModuleData moduleData;
		while(getline(input_file_stream1,line))
		{
			if (line.empty() && input_file_stream1.peek() == EOF)
			{
				// No-Op
			}
			else
			{
				lineNumber++;
				tokenOffset = 0;
			}
			//cout << "LINE#" << lineNumber << ": " << line << endl;
			if (!validators.empty())
			{
				tokenizerPassOne(line,lineNumber,tokenOffset,validators,symbolTable,moduleData);
			}
		}
		if (!validators.empty())
		{
			
			ValidatorData* validator = validators.front();
			// We got here because there were still tokens to process based on token count
			// provided at the start of each line, but tokenCount was not fully decremented to zero.
			if (validator->tokenCount > 0)
			{
				//cout << "Validator tokenCount is > than zero" << endl;
				char* p_token = NULL;
				//TODO: move token increment into tokenizerPassOne? this'll be hard to keep track of
				tokenOffset++; // Increment because it was the 'next' token that failed to process
				unsigned int is_valid_syntax = validator_handler(p_token,validator,symbolTable,moduleData);
				//cout << "is_valid_syntax == " << is_valid_syntax << endl;
				if (is_valid_syntax > 0)
				{
					exit_on_parse_error(is_valid_syntax,lineNumber,tokenOffset);
				}
			}
		}
		// Print Symbol Table
		symbolTable.print_symbol_table();

		// Delete dynamically allocated memory
		delete_validator_queue(validators);
	}
	// Close input file stream 1
	input_file_stream1.close();
		
	// Pass Two
	ifstream input_file_stream2;
	input_file_stream2.open(input_file_name);
	if (input_file_stream2.is_open())
	{
		cout << "\nMemory Map" << endl;

		string line;
		//TODO i think lineNumber and tokenOffset can be deleted for Pass Two
		unsigned int lineNumber = 0;
		unsigned int tokenOffset = 0;
		queue<ValidatorData*> validators = initialize_validator_queue();
		ModuleData moduleData;
		while(getline(input_file_stream2, line))
		{
			lineNumber++;
			//tokenOffset = 0;
			//cout << "LINE# " << lineNumber << ": " << line << endl;
			if (!validators.empty()) 
			{
				//TODO: i don't think we need lineNumber and tokenOffset for 2nd pass
				tokenizerPassTwo(line,lineNumber,tokenOffset,validators,symbolTable,moduleData);
			}
		}

		// Delete dynamically allocated memory at end of program
		moduleData.print_unused_symbols_from_program();
		moduleData.clear_symbols_from_use_set();
		delete_validator_queue(validators);
		symbolTable.delete_symbol_table_keys();
		input_file_stream2.close();
	}
	// Close input file stream 2
	input_file_stream2.close();
}


