#include <events.h>

#include <iostream> // cout, endl
#include <sstream> 
#include <string>   // getline
#include <string.h> //strtok
#include <vector>   // push_back
#include <stdlib.h> // strtoul


// Constructor
Events::Events(const char* input_file) 
{
	if (input_file != NULL
		&& strlen(input_file) > 0)
	{
		_events.open(input_file);
	}
	else
	{
		cerr << "Failed to open file: " << input_file << endl;
	}
}

// Destructor
Events::~Events()
{
	if(_events.is_open())
	{
		_events.close();
	}
	else
	{
		cerr << "Failed to close Events stream." << endl;
	}
}

/*
 * Open file stream. 
 * Read one line delimited by newline. 
 * Convert line to c_string.
 * Tokenize by whitespace and store in vector
 * Initialize Process with values from vector
 * 
 * &return: pointer to Process, NULL on error
 */
Process* Events::get_event()
{
	Process* process = NULL;

	if(_events.is_open())	
	{	
		// Read event from events stream
		string line;
		getline(_events, line, '\n');
		
		// Return NULL if end of file reached.
		if(_events.eof())       
        	{                               
                	return process; 
		}
		cout << "LINE: " << line << endl;
		
		// Create new c_string from line
		char* c_string = new char [line.length()+1];
        	strcpy(c_string,line.c_str());
		
		// Tokenize line on whitespace and store in vector
		vector<unsigned int> tokens;
		static const char* delims = " \t";
		char* token = strtok(c_string,delims);
		while (token != NULL)
		{
			tokens.push_back( 
				(unsigned int)strtoul(
					token,
					NULL,
					10) );	
			token = strtok(NULL,delims);
		}
		
		// Delete c_string
		delete c_string;		

		// Create process for event
		static unsigned int num_process_inputs = 4;
		if (tokens.size() >= num_process_inputs)
		{
			process = new Process(tokens[0], // Arrival Time							
					tokens[1],       // Total CPU Time
					tokens[2],       // CPU Burst
					tokens[3]);      // IO Burst
		}
		else
		{
			cerr << "Failed to create Process from event stream. Number of process inputs insufficient." << endl;
		}
	}
	else
	{
		cerr << "Failed to create Proccess from event stream. Events stream is not open." << endl;
	}
	return process;
}

