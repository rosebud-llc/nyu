#ifndef INCLUDED_RANDS_HEADER
#define INCLUDED_RANDS_HEADER

#include <vector>
#include <fstream>  // is_open, close
using namespace std;

class Rands
{

public:
	Rands(const char* random_file);
	~Rands();

	// getters
	unsigned int get_next_random_value(unsigned int cpu_burst);


private:
	ifstream _random_stream;
	vector<unsigned int> _random_values;	
	vector<unsigned int>::const_iterator _random_value_itr;

	void _init_random_values();
};

#endif
