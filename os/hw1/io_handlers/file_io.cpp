#include <file_io.h>

#include <log_io.h>  // getLogPrefix

#include <iostream> // cout, endl
#include <string.h> // strlen


void loadFileStream(const char* input_file_name, ifstream& input_file_stream)
{
	if (strlen(input_file_name) > 0)
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "Converting " << input_file_name << " to file stream." << endl;
		input_file_stream.open(input_file_name);
	}
	else
	{
		cout << getLogPrefix(__FILE__,__func__,__LINE__) << "ERROR: Unable to open file because input_file_name is empty string." << endl;
	}
}
