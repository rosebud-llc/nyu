#include <io_handlers/args_io.h>
#include <events/events.h>

#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


void print_state_transition_info(
	Event* event,
	Process* process,
	unsigned int timestamp,
	unsigned int elapsed_time) // TODO: what is this measuring again?
{
	cout << timestamp << " " << process->get_pid() << " " << elapsed_time
		<< ": " << event->get_event_state_str(event->get_curr_state())
		<< " -> "
		<< event->get_event_state_str(event->get_next_state());
	if (event->get_curr_state() != Event::CREATED)
	{
		if(event->get_next_state() == Event::RUNNING)
		{
			cout << "cb=" << process->get_cpu_burst()
				<< " rem=" << process->get_total_cpu_time();
			//TODO: add priority print 
		}
		else if(event->get_next_state() == Event::BLOCK)
		{
			cout << "ib=" << process->get_io_burst()
				<< " rem=" << process->get_total_cpu_time();
			//TODO: add priroity print
		}
	}
	cout << "\n";
}	

int evaluate_state_transition(
	Event* event,
	Process* process,
	unsigned int timestamp)
{
	int rc = 0;
	switch(event->get_next_state())
	{
		case Event::READY:
			print_state_transition_info(
				event,
				process,
				timestamp,
				0); //TODO: what should elasped time or 'how long' be?
			break;		

		/*case Event::PREEMPT:
			break;
		*/
		case Event::RUNNING:
			break;

		case Event::BLOCK:
			break;
	}
	return rc;
}

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
	Process* process;
	unsigned int current_timestamp;
	Event::EVENT_STATE prev_state;
	Event::EVENT_STATE curr_state;
	Event::EVENT_STATE next_state;
	//unsigned int time_in_previous_state;
	while (event = events.get_front_event())
	{
		/*
 		if (Event::CREATED == event->get_event_state())
		{
			cout << "event is in state created" << endl;
		}
		events.add_completed_process(event->get_process());
		delete event;
		event = NULL;
		events.pop_front_event();
		*/
		process = event->get_process();
		current_timestamp = event->get_timestamp();
		//prev_state = event->get_prev_state();
		//curr_state = event->get_curr_state();
		//next_state = event->get_next_state();	
		if (event->get_curr_state() == Event::CREATED)
		{
			event->set_next_state(Event::READY);		
		}
		event->print_event_info();
		//time_in_previous_state = current_timestamp - process->get_timestamp();
		
		evaluate_state_transition(event, process, current_timestamp);
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


