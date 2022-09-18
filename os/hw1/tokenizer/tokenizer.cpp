#include <tokenizer.h>

#include <io_handlers/log_io.h> // getLogPrefix
#include <string.h> // strtok
#include <iostream> // cout, endl
#include <fstream>  // getline, is_open, close


unsigned int tokenizeLine(string& line, const char* delims, unsigned int counter)
{
	cout << line << endl;
	// Allocate mem in order to convert string to char*
	char* p_cstring = new char [line.length()+1];
	strcpy(p_cstring,line.c_str());
	// Tokenize first substring by delimeters
	char* p_char = strtok(p_cstring,delims);
	//TODO: is this the preferred method to check if NULL or empty string?
	while (p_char != 0)
	{
		cout << p_char << endl;
		// Start of linker || ready for next validator || new line has zero items to read
		if (counter == 0)
		{
			//TODO: reset_counter(counter,p_char);
			// If counter is still zero though, you don't want to move to next Validator, so you need to add some check here
		}

		p_char = strtok(NULL,delims);
	}
	// Deallocate mem
	delete[] p_cstring;
	return counter;
}

void processFileStream(ifstream& input_file_stream)
{
	if (input_file_stream.is_open())
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "Start reading from file stream." << endl;
		string line;
		const char* delims = " \t\n";
		unsigned int counter(0);
		while(getline(input_file_stream, line))
		{
			counter = tokenizeLine(line,delims,counter);
		}
		input_file_stream.close();
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "Finished reading from file stream." << endl;
	}
	else
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "ERROR: Unable to open file stream." << endl;
	}
}
