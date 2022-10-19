#include <io_handlers/args_io.h>
#include <events/events.h>

#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


int main(int argc, char* argv[])
{
	// Return code;
	int rc = 0;
	
	// Parse args
	Args args;
	rc = get_args(argc,argv,args);
	if (rc)
	{
		cerr << "Stopping program." << endl;
		return rc;
	}
	else
	{
		print_args(args);
	}
	

	// Read-in random values
	vector<unsigned int> rands 
		= getRandomValues(args.random_file.c_str());
	
	// Create events list 
	Events events(args.input_file.c_str());	

	Event* event;
	while (event = events.get_front_event())
	{
		if (Event::CREATED == event->get_event_state())
		{
			cout << "event is in state created" << endl;
		}
		events.add_completed_process(event->get_process());
		delete event;
		event = NULL;
		events.pop_front_event();
		
	}
	events.print_summary(args.scheduler_specification);

	
	// Create processes from events stream
	/*
	unsigned int next_event_timestamp = 0;
	unsigned int time_elapsed = 0;
	vector<unsigned int>::const_iterator rands_itr = rands.begin();
	unsigned int random;

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
		*/
	
	return 0;
}


