#include <io_handlers/args_io.h>
#include <events/events.h>
#include <rands/rands.h>
#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


void print_state_transition_info(
	Process* const process,
	Rands& rands,
	unsigned int& timestamp, //timestamp is updated if current event state is RUNNING or BLOCK
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state) 
{
	cout << timestamp << " " << process->get_pid() << " " << process->get_elapsed_time()
		<< ": " 
		<< Event::get_event_state_str(curr_state)
		<< " -> "
		<< Event::get_event_state_str(next_state); 
		
	switch(curr_state)
	{
		case Event::RUNNING:
			{
			unsigned int cpu_burst =
				rands.get_next_random_value(
					process->get_cpu_burst());
			process->set_elapsed_time(cpu_burst);
			timestamp += cpu_burst;
			
			cout << " cb=" << cpu_burst
				<< " rem=" << 
					(process->get_total_cpu_time()
					- process->get_elapsed_time());
			//TODO: add priority print
			} 
			break;
		case Event::BLOCK:
			{
			unsigned int io_burst =
				rands.get_next_random_value(
					process->get_io_burst());
			timestamp += io_burst;

			cout << " ib=" << io_burst
				<< " rem=" << 
					(process->get_total_cpu_time()
					- process->get_elapsed_time());
			//TODO: add priroity print
			}
			break;
		default:
			// do not update timestamp
			// do not print info
			;
	}
	cout << "\n";
}	


void print_add_event_info(
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
		cout << "AddEvent("
			<< timestamp
			<< ":" << process->get_pid()
			<< ":" << Event::get_event_state_str(next_state)
			<< "):";
                cout << " ";
                events.print_events();
                cout << "==> "; 
		events.add_event(process,
                        timestamp,
                        curr_state,
                        next_state);
                events.print_events(); 
		cout << "\n";
	}
}

int evaluate_state_transition(
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
	switch(next_state)
	{
		case Event::READY:
			print_state_transition_info(
				process,
				rands,
				timestamp,
				curr_state,
				next_state);
                        curr_state = Event::READY;
                        next_state = Event::RUNNING;
			run_queue.push_front(process);
			call_scheduler = true;
			break;		

		/*case Event::PREEMPT:
			break;
		*/
		case Event::RUNNING:
			print_state_transition_info(
				process,
				rands,
				timestamp,
				curr_state,
				next_state);
                        curr_state = Event::RUNNING;
                        next_state = Event::BLOCK;
			print_add_event_info(
                        	events,
                        	rands,
                        	process,
                        	timestamp,
                        	curr_state,
                        	next_state);
			//call_scheduler = true;
			break;

		case Event::BLOCK:
			print_state_transition_info(
				process,
				rands,
				timestamp,
				curr_state,
				next_state);
			curr_state = Event::BLOCK;
                        next_state = Event::READY;
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


int scheduler_handler(list<Process*>& run_queue, 
	Events& events,
	Rands& rands,
	unsigned int timestamp,
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state)
{
	int rc = 0;
	// should scheduler return next process from run_queue or will run queue already be properly sorted/prioritized?
	Process* const process = run_queue.front();
	print_scheduler_info(process, run_queue.size());
	if (process != NULL)
	{
		print_add_event_info(
			events,
			rands,
			process,
			timestamp,
			curr_state,
			next_state);
		run_queue.pop_front(); //Removing the process from the run queue
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
	Events events(args.input_file.c_str());	

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
		evaluate_state_transition(events,
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
			scheduler_handler(run_queue,
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


