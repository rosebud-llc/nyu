#include <rands.h>

#include <iostream> // cout, endl
#include <string>   // getline
#include <string.h> // strlen, strcpy
#include <stdlib.h> // strtoul
#include <algorithm> // max

// Constructor
Rands::Rands(const char* input_file) 
{
        if (input_file != NULL
                && strlen(input_file) > 0)
        {
                _random_stream.open(input_file);
                _init_random_values();
        }
        else
        {
                cerr << "Failed to open file: " << input_file << endl;
        }
}

// Destructor
Rands::~Rands()
{
        if(_random_stream.is_open())
        {
                _random_stream.close();
        }
        else
        {
                cerr << "Failed to close Random stream." << endl;
        }
}

//TODO input may be cpu or io burst
unsigned int max_random_value(
	unsigned int random_value, 
	unsigned int cpu_burst)
{
        unsigned int max_random_value = 
		1 + (random_value % cpu_burst);
        if (max_random_value > cpu_burst)
        {
                max_random_value = cpu_burst;
        }
	return max_random_value;	
}


//TODO input may be cpu or io burst
unsigned int Rands::get_next_random_value(unsigned int cpu_burst)
{
	unsigned int random_value;
	if (_random_value_itr == _random_values.end())
	{
		_random_value_itr == _random_values.begin();
	}
	random_value = max_random_value(
		*_random_value_itr, 
		cpu_burst);
	_random_value_itr++;
	return random_value;
}

void Rands::_init_random_values()
{
        if(_random_stream.is_open())
        {
                string line;
                bool skip_first_line = false;
                while(getline(_random_stream,line,'\n'))
                {
                        char* rand_value = new char[line.length()+1];
                        strcpy(rand_value,line.c_str());
                        if(!skip_first_line)
                        {
                                unsigned int line_count
                                        = (unsigned int)strtoul(rand_value,NULL,10);
                                _random_values.reserve(line_count);
                                skip_first_line = true;
                                delete rand_value;
                                continue;
                        }
                        _random_values.push_back(
                                (unsigned int)strtoul(rand_value,NULL,10));
                        delete rand_value;
                }
		// init _random_value_itr as well
		_random_value_itr = _random_values.begin();
        }
        else
        {
                cerr << "Failed to open _random_stream: " << endl;
        }
        //cout << "Total random values added to vector: " << _random_values.size() << endl;
}

