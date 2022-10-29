#include <io_handlers/args_io.h>
#include <events/events.h>
#include <rands/rands.h>
#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


void print_state_transition_info(
	Process* const process,
	const unsigned int timestamp, 
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state, 
	const unsigned int burst=0)
{
	cout << timestamp << " " << process->get_pid() << " " << process->get_elapsed_time()
		<< ": " 
		<< Event::get_event_state_str(curr_state)
		<< " -> "
		<< Event::get_event_state_str(next_state); 

	if (next_state == Event::RUNNING || next_state == Event::BLOCK)
	{
		if (next_state == Event::RUNNING)
		{
			cout << " cb=";
		}
		else if (next_state == Event::BLOCK)
		{
			cout << " ib=";
		}
		cout << burst	 
			<< " rem=" << 
				(process->get_total_cpu_time()
				- process->get_elapsed_time())
			<< " prio=" << process->get_dynamic_priority();
	}
	cout << "\n";	
}	


void print_add_event_info(
	Args& args,
	Events& events,
	Rands& rands,
	Process* const process,
	unsigned int timestamp,
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state)
{
	if (process == NULL)
	{
		cerr << "ERROR: Process is NULL. Unable to print_add_event_info()." << endl;
	}
	else
	{
		if (args.trace_event_queue)
		{
			cout << "AddEvent("
				<< timestamp
				<< ":" << process->get_pid()
				<< ":" << Event::get_event_state_str(next_state)
				<< "):";
        	        cout << " ";
			events.print_events();
			cout << "==> "; 
		}
		events.add_event(process,
                        timestamp,
                        curr_state,
                        next_state);
                if (args.trace_event_queue)
		{
			events.print_events(); 
			cout << "\n";
		}
	}
}

int evaluate_state_transition(
	Args& args,
	Events& events,
	Rands& rands,
	Process* process,
	list<Process*>& run_queue,
	unsigned int& timestamp, //gets updated when next state is RUNNING or BLOCK
	Event::EVENT_STATE& curr_state,
	Event::EVENT_STATE& next_state,
	bool& call_scheduler)
{
	int rc = 0;
	unsigned int burst = 0;
	switch(next_state)
	{
		case Event::READY:
			if (args.trace_state_transition)
			{
				print_state_transition_info(
					process,
					timestamp,
					curr_state,
					next_state);
                        }
			curr_state = Event::READY;
                        next_state = Event::RUNNING;
			run_queue.push_front(process);
			call_scheduler = true;
			break;		

		/*case Event::PREEMPT:
			break;
		*/
		case Event::RUNNING:
			burst = rands.get_next_random_value(
					process->get_cpu_burst());
			if(args.trace_state_transition)
			{	
				print_state_transition_info(
					process,
					timestamp,
					curr_state,
					next_state,
					burst);
			}
			//TODO - we know this is incorrect place to set_elapsed_time. it should happen in BLOCK
			process->set_elapsed_time(burst);
                        curr_state = Event::RUNNING;
                        next_state = Event::BLOCK;
			timestamp += burst;
			print_add_event_info(
                        	args,
				events,
                        	rands,
                        	process,
                        	timestamp,
                        	curr_state,
                        	next_state);
			//call_scheduler = true;
			break;

		case Event::BLOCK:
			//TODO assuming you can only get to BLOCK when previous/curr state is RUNNING
			// this means the process ran for some duration of cpu_burst (remember it could have been pre-empted)
			// so it is here where we should process->set_elapsed_time() using currennt timestamp relative to previous
			// timestamp
			// TODO: set_elapsed_time may not always be full burst on preempt - maybe it's okay here, but in PREEMPT need to handle
			//process->set_elapsed_time(timestamp - prev_timestamp);	

			burst = rands.get_next_random_value(
					process->get_io_burst());
			if (args.trace_state_transition)
			{
				print_state_transition_info(
					process,
					timestamp,
					curr_state,
					next_state,
					burst);
			}
			curr_state = Event::BLOCK;
                        next_state = Event::READY;
                        timestamp += burst;
			print_add_event_info(
                                args,
				events,
                                rands,
                                process,
                                timestamp,
                                curr_state,
                                next_state);			
			call_scheduler = true;
			break;
		default:
			cerr << "ERROR: Evaluating a transition state that should not be evaluated" << endl;
	}
	return rc;
}


void print_scheduler_info(Process* const process,
	unsigned int run_queue_size)
{
	if (process == NULL)
	{
		cout << "SCHED (" << run_queue_size << ")" << endl;	
	}
	else
	{
		cout << "SCHED (" << run_queue_size 
			<< ") " << process->get_pid() 
			<< ":" << process->get_arrival_time() << endl; //TODO: should this be current_timestamp??
	}
}


int scheduler_handler(
	Args& args,
	list<Process*>& run_queue, 
	Events& events,
	Rands& rands,
	unsigned int timestamp,
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state)
{
	int rc = 0;
	// should scheduler return next process from run_queue or will run queue already be properly sorted/prioritized?
	Process* const process = run_queue.front();
	if (args.trace_event_execution)
	{
		print_scheduler_info(process, run_queue.size());
	}
	if (process != NULL)
	{
		print_add_event_info(
			args,
			events,
			rands,
			process,
			timestamp,
			curr_state,
			next_state);
		run_queue.pop_front(); //TODO - should this happenn before above print? Removing the process from the run queue
	}
	// else, process is NULL and there's no event to schedule
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
	

	// Creates random values
	Rands rands(args.random_file.c_str());
	
	// Create events list 
	Events events(
		args.input_file.c_str(),
		args.maxprio,
		rands);	

	Event* event;
	Process* process;
	list<Process*> run_queue; //TODO: move to a separate class for run queue
	bool call_scheduler = false;
	unsigned int current_timestamp;
	Event::EVENT_STATE prev_state;
	Event::EVENT_STATE curr_state;
	Event::EVENT_STATE next_state;
	//unsigned int time_in_previous_state;
	while (event = events.get_front_event())
	{
		process = event->get_process();
		current_timestamp = event->get_timestamp();
		curr_state = event->get_curr_state();
		next_state = event->get_next_state();
		delete event;
		event = NULL;
		events.pop_front_event();
		//time_in_previous_state = current_timestamp - process->get_timestamp();
		
		// Switch Case State Transition
		evaluate_state_transition(
			args,
			events,
			rands,
			process, 
			run_queue, 
			current_timestamp,
			curr_state,
			next_state, 
			call_scheduler);
		
		//cout << "Random value: " <<  rands.get_next_random_value(process->get_cpu_burst()) << endl;		

		// Call Scheduler Handler
		if (call_scheduler)
		{
			//if (get_next_event_time() == current_timestamp)
				//continue;
			call_scheduler = false;
			scheduler_handler(
				args,
				run_queue,
				events,
				rands,
				current_timestamp,
				curr_state,
				next_state);				
			/*if (current_running_process == NULL)
			{
				current_running_process = scheduler->get_next_process();
				if (current_running process = NULL)
				{
					continue
				}
				// create event for this process
			}*/
		}

	}
	events.print_summary(args.scheduler_specification);

	return 0;
}


