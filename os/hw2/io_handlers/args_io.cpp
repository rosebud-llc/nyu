#include <args_io.h>

#include <iostream> // cout, endl
#include <fstream>  // ifstream
#include <string.h> // strcmp, strlen
#include <stdlib.h> // strtoul

//TODO: this will break in the face of "./main -b bogus1 bogus2 -i input_file.txt"
vector<pair<const char*,const char*> > parseArgs(int argc, char* argv[])
{
	vector<pair<const char*,const char*> > args;
	// Check if there are extra args besides the executable
	if (argc > 1)
	{
		const char* first_arg;
		const char* second_arg;
		for(int i=0; i < argc; ++i)
		{
			// Skip first arg, which is the executable
			if (i == 0)
			{
				continue;
			}
			//cout << "Arg: " << argv[i] << endl;
			if(i % 2 == 1)
			{
				first_arg = argv[i];
			}
			else
			{
				second_arg = argv[i];
				//cout << "Adding arg pair: (" << first_arg << ", " << second_arg << ") "<< endl;
				args.push_back(make_pair(first_arg, second_arg));
			}
		}
	}
	return args;
}

const char* getInputFileName(vector<pair<const char*,const char*> > args, const char* arg)
{
	const char* input_file_name = "";
	for(vector<pair<const char*, const char*> >::const_iterator it = args.begin();
			it != args.end(); ++it)
	{
		if(strcmp(it->first,arg) == 0)
		{
			input_file_name = it->second;
			break;
		}
	}
	if (strlen(input_file_name) == 0)
	{
		cerr << "ERROR: Unable to get input file: " << input_file_name << " for  argument: " << arg << endl;
	}
	return input_file_name;
}

vector<unsigned int> getRandomValues(const char* random_file)
{
	vector<unsigned int> rands;
	ifstream random_file_stream;
	random_file_stream.open(random_file);
	if(random_file_stream.is_open())
	{
		string line;
		bool skip_first_line = false; 
		while(getline(random_file_stream,line,'\n'))
		{
			char* rand_value = new char[line.length()+1];
			strcpy(rand_value,line.c_str());
			if(!skip_first_line)
			{
				unsigned int line_count 
					= (unsigned int)strtoul(rand_value,NULL,10);
				rands.reserve(line_count);
				skip_first_line = true;
				delete rand_value;
				continue;
			}
			rands.push_back(
				(unsigned int)strtoul(rand_value,NULL,10));
			delete rand_value;
		}
		random_file_stream.close();
	}
	else
	{
		cerr << "Failed to open ranndom file: " << random_file << endl; 
	}
	cout << "Total random values added to vector: " << rands.size() << endl;
	return rands;
}





