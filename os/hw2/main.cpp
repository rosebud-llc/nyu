#include <io_handlers/args_io.h>
#include <events/events.h>
#include <rands/rands.h>
#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


void print_state_transition_info(
	Event* const event,
	Process* const process,
	unsigned int timestamp) 
{
	cout << timestamp << " " << process->get_pid() << " " << process->get_elapsed_time()
		<< ": " << event->get_event_state_str(event->get_curr_state())
		<< " -> "
		<< event->get_event_state_str(event->get_next_state());
	if (event->get_curr_state() != Event::CREATED)
	{
		if(event->get_next_state() == Event::RUNNING)
		{
			cout << " cb=" << process->get_cpu_burst()
				<< " rem=" << process->get_total_cpu_time();
			//TODO: add priority print 
		}
		else if(event->get_next_state() == Event::BLOCK)
		{
			cout << " ib=" << process->get_io_burst()
				<< " rem=" << process->get_total_cpu_time();
			//TODO: add priroity print
		}
	}
	cout << "\n";
}	

int evaluate_state_transition(
	Event* event,
	Process* process,
	list<Process*>& run_queue,
	unsigned int timestamp,
	bool& call_scheduler)
{
	int rc = 0;
	switch(event->get_next_state())
	{
		case Event::CREATED:
			event->set_curr_state(Event::CREATED);
			event->set_next_state(Event::READY);
			print_state_transition_info(
				event,
				process,
				timestamp);
			run_queue.push_front(process);
			call_scheduler = true;
			break;
		case Event::READY:
			event->set_curr_state(Event::READY);
			event->set_next_state(Event::RUNNING);
			print_state_transition_info(
				event,
				process,
				timestamp);
			call_scheduler = true;
			break;		

		/*case Event::PREEMPT:
			break;
		*/
		case Event::RUNNING:
			event->set_curr_state(Event::BLOCK);
			event->set_next_state(Event::READY);
			print_state_transition_info(
				event,
				process,
				timestamp);
			call_scheduler = true;
			break;

		case Event::BLOCK:
			event->set_curr_state(Event::BLOCK);
			event->set_next_state(Event::READY);
			print_state_transition_info(
				event,
				process,
				timestamp);
			call_scheduler = true;
			break;
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

void print_add_event_info(Process* const process,
	Event::EVENT_STATE next_state,
	Events& events)
{
	if (process == NULL)
	{
		cerr << "ERROR: Process is NULL. Unable to print_add_event_info()." << endl;
	}
	else
	{
		cout << "AddEvent("
			<< process->get_arrival_time() //TODO should this be current_timestamp??
			<< ":" << process->get_pid()
			<< ":" << next_state;
			// call Events function that loops over list and prints each event's info
			// call Events function that creates new event for process
			// update process? in which case you must make it non-const
			// call Events function that loops over list again to print each event's info
		cout << "\n";
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
		print_add_event_info(process,next_state,events);
		
		events.add_event(process,
			rands.get_next_random_value(process->get_cpu_burst()),
			timestamp,
			curr_state,
			next_state);
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
		//time_in_previous_state = current_timestamp - process->get_timestamp();
		
		// Switch Case State Transition
		evaluate_state_transition(event, process, run_queue, current_timestamp, call_scheduler);
		curr_state = event->get_curr_state();
		next_state = event->get_next_state();
		delete event;
		event = NULL;
		events.pop_front_event();
		
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


