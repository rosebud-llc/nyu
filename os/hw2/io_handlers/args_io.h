#ifndef INCLUDED_ARGS_IO_HEADER
#define INCLUDED_ARGS_IO_HEADER

#include <vector>
#include <utility> //Pair
#include <string>
using namespace std;

struct Args
{
	// Verbose
	bool trace_state_transition; // -v
	bool trace_event_execution;  // -t
	bool trace_event_queue;      // -e
	bool trace_preemption;       // -p
	// Scheduler Specifications
	string scheduler_specification; // -s
	unsigned int quantum;    
	unsigned int maxprio;    // DEFAULT == 4
	// Input Files
	string input_file;   // space delimited <unsigned int>'s "AC TC CB IO" per newline 
	string random_file;  // first line is total line count; every subsequent line <unsigned int>
};

void init_args(Args& args);

void print_args(const Args& args);

unsigned int parse_scheduler_specification(
	const char* spec, 
	Args& args);

// public
unsigned int get_args(int argc, 
	char* argv[], 
	Args& args);



#endif
