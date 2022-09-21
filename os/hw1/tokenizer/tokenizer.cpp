#include <tokenizer.h>

#include <io_handlers/log_io.h> // getLogPrefix
#include <string.h> // strtok
#include <stdlib.h> // strtol, EXIT_FAILURE
#include <iostream> // cout, endl
#include <fstream>  // getline, is_open, close
#include <map>


#include <validator_data/validator_data.h>
#include <validator_handlers/validator_handler.h>
#include <validator_queue/validator_queue.h> // initialize_validator_queue, delete_validator_queue, reorder_validator_queue
using namespace std;

// MAP should be used for symbol table because there may be more than one definition for a symbol and you should default to using the first one provided
// NOTE according to lab1_assign.Z test outputs the Symbol Table appears to be Key Ordered

// You MUST keep ordered list of USE list symbols on second pass so that you know how which symbol to apply for an E instruction
// you can have up to 256 symbols  so it's not always the last digit you need to check, but the last 3 of the instruction

map<char*, unsigned int> symbol_table;


void exit_on_parse_error(unsigned int errorCode,
		unsigned int lineNum, unsigned int lineOffset)
{
	static const char* errorString[] = {
			"SUCCESS"                  // (0) No error
			"NUM_EXPECTED",            // (1) Number expected, anything >= 2^30 is not a number either
			"SYM_EXPECTED",            // (2) Symbol expected
			"ADDR_EXPECTED",           // (3) Addressing expected which is A/E/I/R
			"SYM_TOO_LONG",            // (4) Symbolg Name is too long
			"TOO_MANY_DEF_IN_MODULE",  // (5) > 16
			"TOO_MANY_USE_IN_MODULE",  // (6) > 16
			"TOO_MANY_INSTR",          // (7) total num_instr exceeds memory size (512)
	};
	if (errorCode > 0)
	{
		cout << "Parse Error line " << lineNum << " offset " << lineOffset << ": " << errorString[errorCode] << endl;
		exit(EXIT_FAILURE);
	}
}

char* convert_string_to_cstring(string& line)
{
	char* p_cstring = new char [line.length()+1];
	strcpy(p_cstring,line.c_str());
	return p_cstring;
}

//TODO move set_count into validator_handler ?
void set_count(char* p_token,
		ValidatorData* validator)
{
	cout << "P_TOKEN - GIVEN COUNT: " << p_token << endl;
	long int count = strtol(p_token,NULL,10);

	//TODO: if def_validator or prog_validator, count needs to be multiplied by 2 since you're dealing with paired (S,R) and (type, instr) entries to process
	if (validator->validatorType == 0 || validator->validatorType == 2)
	{
		//Set base address current and next before doubling
		//TODO: if validator handles nextToken this should be moved further upstream
		if (validator->validatorType == 2)
		{
			validator->currBaseAddress = validator->nextBaseAddress;
			validator->nextBaseAddress = (unsigned int)count;
			cout << "BASE ADDRESS.CURR = " << validator->currBaseAddress << endl;
			cout << "BASE ADDRESS.NEXT = " << validator->nextBaseAddress << endl;
		}
		count = count * 2;
		cout << "P_TOKEN - COUNT DOUBLED" << endl;
	}
	(count >= 0) ? validator->tokenCount = (unsigned int)count : 0; // TODO: Set count to 0 if count < 0 ? And Skip?
	cout << "P_TOKEN - SET COUNT: " << validator->tokenCount << endl;
}


void count_handler(char* p_token,
		ValidatorData* validator,
		queue<ValidatorData*>& validators)
{
	set_count(p_token, validator);
	//If count STILL zero even after parsing token count, then move to next validator
	//TODO: move this into tokenize so that you can move count_handler into valdaitor_handler folder without needing to include queue logic
	if (validator->tokenCount == 0)
	{
		reorder_validator_queue(validators);
		cout << "QUEUE REORDERED - LINE COUNT ZERO" << endl;
	}
}

char* nextToken(char* p_token, const char* delimiters, unsigned int& tokenOffset)
{
	++tokenOffset;
	return strtok(p_token,delimiters);
}


// TODO pass lineNumber and offsetNumber from processFileStreeam to tokenize()
// increment as needed
void tokenize(string& line,
		const char* delims,
		unsigned int lineNumber,
		unsigned int tokenOffset,
		queue<ValidatorData*>& validators,
		vector<char*>& useSymbolsList)
{
	char* p_cstring = convert_string_to_cstring(line);
	// Next Token
	char* p_token = nextToken(p_cstring,delims,tokenOffset);
	while (p_token != 0)
	{
		ValidatorData* validator = validators.front();
		// Start of linker file || ready for next validator || new line has zero items to read
		if (validator->tokenCount == 0)
		{
			// First, validate count
			unsigned int is_valid_count = validator_handler(p_token, validator, true);
			cout << "Is Valid Count: " << is_valid_count << endl;
			if (is_valid_count > 0)
			{
				exit_on_parse_error(is_valid_count,lineNumber,tokenOffset);
			}
			//TODO: need to handle count validation here with count_handler, but similar to validator_handler using if/else if/else to
			// know which is_valid_token_count implementation to use
			// Set Count TODO: this count is for number of args (or pairs of args) to process for the line - name it better than count handler
			// Then set count
			count_handler(p_token, validator, validators);
			// Next Token
			p_token = nextToken(NULL,delims,tokenOffset);
		}
		/*
		 * TODO:
		 * - IGNORE this one line, do everything else more or less: -----do not double the count in set_count() and count_handler() functions
		 * - instead, rely on validator.first->get_validator_enum() to check which vaidator to run (def/use/prog)
		 * - given validator, you'll call strtok only once (for use symbol) or twice (to build a def or prog pair)
		 * - then pass the resultant data as Templated Struct so you can send any kind of struct to factory process()
		 * - if (def) -> process pairs (Symbol, Relative Address) -> return (Symbol, Absolute Address) -> add to symbol_table map -> error if it already exists?
		 * - if (use) -> process use list (Symbol, 0-based Order in List) -> return (Symbol, 0-based Order in List) i.e. do nothing, append output to saved vector
		 * - if (prog) -> process instructions using base address for R and useList for E (Type, Instruction, SymbolTable) -> return modified Instruction
		 * - you could try to proactively clean up here or rely on provided counts to be correct
		 *
		 */
		while(p_token != 0) //validator.second > 0 && ?
		{
			unsigned int is_valid_syntax = validator_handler(p_token, validator);
			cout << "Is Valid Syntax: " << is_valid_syntax << endl;
			if (is_valid_syntax > 0)
			{
				exit_on_parse_error(is_valid_syntax,lineNumber,tokenOffset);
			}

			// Next Token
			p_token = nextToken(NULL,delims,tokenOffset);
			// Case where Definition Count set to 0 because there's nothing to process, you don't want to decrement  to negative value.. altho not posisble if this is unsigned int, but better to check and be sure
			if (validator->tokenCount > 0)
			{
				validator->tokenCount--;
			}
			cout << "VALIDATOR COUNT: " << validator->tokenCount << endl;
			if (validator->tokenCount == 0)
			{
				reorder_validator_queue(validators);
				cout << "QUEUE REORDERED - FINISHED PROCESSING" << endl;
				break;
			}
		}
	}
	// Deallocate mem
	delete[] p_cstring;
	return;
}

//TODO: should this produce a symbol_table? Will be need for passTwo
void processFileStream(ifstream& input_file_stream)
{
	if (input_file_stream.is_open())
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "Start reading from file stream." << endl;

		string line;
		unsigned int lineNumber = 0;
		unsigned int tokenOffset = 0;
		const char* delims = " \t\n";
		vector<char*> useSymbolsList;
		queue<ValidatorData*> validators = initialize_validator_queue();
		cout << "Attempting to get first line in file... " << endl;
		while(getline(input_file_stream, line))
		{
			cout << "LINE#" << ++lineNumber << ": " << line << endl;
			if (!validators.empty())
			{
				tokenize(line,delims,lineNumber,tokenOffset,validators,useSymbolsList);
			}
		}

		delete_validator_queue(validators);
		input_file_stream.close();
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "Finished reading from file stream." << endl;
	}
	else
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "ERROR: Unable to open file stream." << endl;
	}
}


