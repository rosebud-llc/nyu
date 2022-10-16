#include <io_handlers/args_io.h>
#include <events/events.h>

#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


int main(int argc, char* argv[])
{
	// Parse args
        vector<pair<const char*,const char*> > args = parseArgs(argc,argv);
	
	// Fetch random values
	const char* arg_r = "-r"; //rfile
	const char* rfile = getInputFileName(args,arg_r);
	vector<unsigned int> rands = getRandomValues(rfile);

	// Create events stream
	const char* arg_i = "-i"; //input
	const char* input_file = getInputFileName(args,arg_i);
	Events events(input_file);	
	
	// Create processes from events stream
	unsigned int next_event_timestamp = 0;
	unsigned int time_elapsed = 0;
	vector<unsigned int>::const_iterator rands_itr = rands.begin();
	unsigned int random;
	Process* process;
	while(process = events.get_event())
	{
		if(process == NULL)
		{		
			break;
		}
		process->set_process_state(Process::CREATED);
		process->print_process();
		process->set_process_state(Process::READY);

		if (rands_itr == rands.end())
		{
			rands_itr = rands.begin();
		}	
		random = *rands_itr;
		++rands_itr;	
		unsigned int max_cpu_burst = max(random,process->get_cpu_burst());
		time_elapsed += max_cpu_burst;
		process->set_total_cpu_time( 
			process->get_total_cpu_time() - max_cpu_burst );
		process->set_process_state(Process::RUNNING);

		if (! (process->get_total_cpu_time() <= 0) )
		{
			process->set_process_state(Process::BLOCKED);
			// TODO: how do you know when enough time has passed to release from blocked state
		}
		else
		{
			// Process has completed running
			delete process;
			
		}
	
	}

	return 0;
}


