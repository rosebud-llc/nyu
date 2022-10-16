#include <args_io.h>

#include <iostream> // cout, endl
#include <string.h> // strcmp, strlen


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

const char* getInputFileName(vector<pair<const char*,const char*> > args)
{
	const char* input_file_name = "";
	for(vector<pair<const char*, const char*> >::const_iterator it = args.begin();
			it != args.end(); ++it)
	{
		if(strcmp(it->first,"-i") == 0)
		{
			input_file_name = it->second;
			break;
		}
	}
	if (strlen(input_file_name) == 0)
	{
		cerr << "ERROR: Unable to find argument \"-i\" for input file name." << endl;
	}
	return input_file_name;
}
