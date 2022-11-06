#include <io_handlers/args_io.h>
#include <events/events.h>
#include <rands/rands.h>
#include <iostream>  // cout, endl
#include <algorithm> // max
using namespace std;


void print_run_queue(Args& args,
	const unsigned int action_type,
	list<Process*>& run_queue,
	Process* process,
	Event::EVENT_STATE next_state)
{
	if (args.trace_run_queue)
	{
		cout << "Run Queue: ";
		list<Process*>::const_iterator it = run_queue.begin();
		for(; it != run_queue.end(); ++it)
		{
			// timstamp, pid, next_state
			cout << (*it)->get_state_transition_timestamp() 
				<< ":" << (*it)->get_pid() 
				<< ":" << Event::get_event_state_str(next_state)
				<< " ";
		}
	}	
	switch(action_type)
	{
		// Add
		case 0:
			//TODO Assert process is not NULL?
			run_queue.push_back(process);
			break;
		// Remove
		case 1:
			run_queue.pop_front();
			break;
		default:
			cerr << "ERROR: invalid action type for run_queue: " << action_type << endl;
	}
	if (args.trace_run_queue)
	{
		cout << " ==> ";
		list<Process*>::const_iterator it = run_queue.begin();
		for(; it != run_queue.end(); ++it)
		{
			// timstamp, pid, next_state
			cout << (*it)->get_state_transition_timestamp()
				<< ":" << (*it)->get_pid() 
				<< ":" << Event::get_event_state_str(next_state)
				<< " ";
		}
		cout << "\n";
	}
	
}

void print_state_transition_info(
	Process* const process,
	const unsigned int timestamp, 
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state, 
	const unsigned int burst=0,
	const unsigned int howlong=0)
{
	cout << timestamp << " " << process->get_pid() << " " << howlong << ":"; 
	
	if (process->is_done())
	{
		cout << " Done" << endl;
		return;
	}
	
	cout << " " 
	     << Event::get_event_state_str(curr_state)
	     << " -> "
	     << Event::get_event_state_str(next_state); 

	if (next_state == Event::RUNNING) 
	{
		cout << " cb=" 
		     << burst	 
		     << " rem=" 
		     << (process->get_total_cpu_time()
			- process->get_elapsed_time())
		     << " prio=" 
		     << process->get_dynamic_priority();
	}
	else if (next_state == Event::BLOCK)
	{
		//TODO: i've added extra whitespace before ib= since that looks to be what test files show...
		cout << "  ib="
		     << burst	 
		     << " rem=" 
		     << (process->get_total_cpu_time()
			- process->get_elapsed_time());
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
	const unsigned int timestamp, 
	const unsigned int elapsed_time, //current_timestamp - process.state_transition_timestamp
	Event::EVENT_STATE& curr_state,
	Event::EVENT_STATE& next_state,
	bool& call_scheduler)
{
	int rc = 0;
	// Following variable only used by print_run_queue
	const unsigned int action_type = 0;
	// Following variables only used by RUNNING and BLOCK
	unsigned int burst = 0;
	unsigned int new_timestamp = 0;
	switch(next_state)
	{
		case Event::READY:			
			// First, update elapsed_block_time -- needed for per process IO Time summary
			process->set_elapsed_block_time(elapsed_time);
			if (args.trace_state_transition)
			{
				print_state_transition_info(
					process,
					timestamp,
					curr_state,
					next_state,
					0, 
					//timestamp - process->get_state_transition_timestamp()
					elapsed_time
					);
                        }
			/*if(curr_state == Event::CREATED)
			{
				curr_state = Event::READY;
                       		next_state = Event::RUNNING;
			}*/
			process->set_state_transition_timestamp(timestamp);
			//run_queue.push_back(process);
			// Push back process to run_queue
			print_run_queue(args,action_type,run_queue,process,next_state);
			call_scheduler = true;
			break;		

		/*case Event::PREEMPT:
			break;
		*/
		case Event::RUNNING:
			//TODO burst should be max(burst,remaining cpu time actually needed for process)
			burst = rands.get_next_random_value(
					process->get_cpu_burst());
			
			if ( (burst + process->get_elapsed_time())
				>= process->get_total_cpu_time() )
			{
				burst = process->get_total_cpu_time()
					- process->get_elapsed_time();
					
			}
			if(args.trace_state_transition)
			{	
				print_state_transition_info(
					process,
					timestamp,
					curr_state,
					next_state,
					burst,
					elapsed_time //process->get_cpu_burst()
					); // elapsed_time //timestamp - process->get_state_transition_timestamp());
			}
			curr_state = Event::RUNNING;
			next_state = Event::BLOCK;
			process->set_state_transition_timestamp(timestamp);
			new_timestamp = timestamp + burst;
			print_add_event_info(args,events,rands,process,new_timestamp,curr_state,next_state);
			call_scheduler = false;
			break;

		case Event::BLOCK:
			//TODO assuming you can only get to BLOCK when previous/curr state is RUNNING
			// this means the process ran for some duration of cpu_burst (remember it could have been pre-empted)
			// so it is here where we should process->set_elapsed_time() using currennt timestamp relative to previous
			// timestamp
			// TODO: set_elapsed_time may not always be full burst on preempt - maybe it's okay here, but in PREEMPT need to handle
			process->set_elapsed_time(elapsed_time);	
			//NOTE: (1) elapsed time must be set before is_done() to be correct
			//      (2) we allow call_scheduler=true because we'll let scheduler clean up completed process for us
			//      (3) TODO should we update state/proces info at all here?
			if (process->is_done())
			{
				//cout << "process is done!" << endl;
				if (args.trace_state_transition)
				{
					print_state_transition_info(
						process,
						timestamp,
						curr_state,
						next_state,
						0,
						elapsed_time //timestamp - process->get_state_transition_timestamp()
						);
				}
				// Even tho process is Done, but update transisition to altest timestamp for correct 
				// per process summary of Finishing time and Turnaround time
				process->set_state_transition_timestamp(timestamp);
				//TODO this can be confusing b/c we're not acctually adding an event, but add_event() handles 
				//     completed processes by adding to _completed_processes and no event actually created.
				curr_state = Event::BLOCK;
				next_state = Event::READY;
				events.add_event(process,
					timestamp,
					curr_state,
					next_state);	
			}
			else
			{
				burst = rands.get_next_random_value(
						process->get_io_burst());
				if (args.trace_state_transition)
				{
					print_state_transition_info(
						process,
						timestamp,
						curr_state,
						next_state,
						burst,
						elapsed_time ////timestamp - process->get_state_transition_timestamp()
						);
				}
				curr_state = Event::BLOCK;
				next_state = Event::READY;
				process->set_state_transition_timestamp(timestamp);
				new_timestamp = timestamp + burst;
				print_add_event_info(args,events,rands,process,new_timestamp,curr_state,next_state);
			}
			call_scheduler = true;
			//cout << "CALL SCHEDULER == " << call_scheduler << " == TRUE" << endl;
			break;
		default:
			cerr << "ERROR: Evaluating a transition state that should not be evaluated" << endl;
	}
	return rc;
}


void print_scheduler_info(list<Process*> run_queue)
{
	if (run_queue.empty())
	{
		cout << "SCHED (" << run_queue.size() << ")" << endl;	
	}
	else
	{
		Process* const process = run_queue.front();
		cout << "SCHED (" << run_queue.size() 
			<< ") " << process->get_pid() 
			<< ":" << process->get_arrival_time() << endl; //TODO: should this be current_timestamp??
	}
}


Process* scheduler_handler(
	Args& args,
	list<Process*>& run_queue, 
	Events& events,
	Rands& rands,
	const unsigned int timestamp,
	Event::EVENT_STATE curr_state,
	Event::EVENT_STATE next_state)
{
	Process* rc = NULL;
	//TODO should scheduler return next process from run_queue or will run queue already be properly sorted/prioritized?
	if (run_queue.empty() && args.trace_event_execution)
	{
		print_scheduler_info(run_queue);
	}
	//TODO When multiple processes all ready with equivalent timestamp, evalute all of them before finsihing scheduler_handler?
	if (!run_queue.empty())
	{
		if (args.trace_event_execution)
		{
			print_scheduler_info(run_queue);
		}
		//TODO prefer to make this const, but need to assign to rc
		Process* const process = run_queue.front();
		rc = process;
		// TODO add scheduler class here to handle resolving timestamp necessary to add_event in correct place

		//FCFS
		unsigned int new_timestamp =
			events.get_timestamp_when_cpu_free(timestamp);
		if (curr_state == Event::CREATED) 
		{
			curr_state = Event::READY;
			next_state = Event::RUNNING;
		}
		else if (curr_state == Event::BLOCK)
		{
			curr_state = Event::READY;
			next_state = Event::RUNNING;
		}
		print_add_event_info(
			args,
			events,
			rands,
			process,
			new_timestamp,
			curr_state,
			next_state);
		//run_queue.pop_front(); //TODO - should this happenn before above print? Removing the process from the run queue
		// Pop front from run_queue
		const unsigned int action_type = 1;
		print_run_queue(args,action_type,run_queue,NULL,next_state);
	}
	//TODO: for each process that remains in run_queue, 
	//      you must update a new property (not yet created as of this writing)
	//      marking how long the processes have been in 'Ready' state (i.e.
	//      left in run_queue without ever being run).
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
		//print_args(args);
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
	Process* current_running_process = NULL;
	list<Process*> run_queue; //TODO: move to a separate class for run queue
	bool call_scheduler = false;
	unsigned int current_timestamp;
	unsigned int elapsed_time;
	Event::EVENT_STATE prev_state;
	Event::EVENT_STATE curr_state;
	Event::EVENT_STATE next_state;
	while (event = events.get_front_event())
	{
		process = event->get_process();
		current_timestamp = event->get_timestamp();
		elapsed_time = current_timestamp - process->get_state_transition_timestamp();
		curr_state = event->get_curr_state();
		next_state = event->get_next_state();
		delete event;
		event = NULL;
		events.pop_front_event();
		
		// Switch Case State Transition
		evaluate_state_transition(
			args,
			events,
			rands,
			process, 
			run_queue, 
			current_timestamp,
			elapsed_time,
			curr_state,
			next_state, 
			call_scheduler);
		//cout << "CALL_SCHEDULDER == " << call_scheduler << endl;	

		// Call Scheduler Handler
		if (call_scheduler)
		{
			// Peak next event to see if it is equivalent arrival time, in which case skip scheduler
			Event* next_event = events.get_front_event();
			if (next_event != NULL)
			{
				//cout << "next_event is NOT NULL" << endl;
				if (next_event->get_timestamp() 
					== current_timestamp)
				{
					//cout << "skipping scheduler b/c timestamps match" << endl;
					//cout << "next_event->get_timestmap(): " << next_event->get_timestamp() << endl;
					//cout << "current_timestamp: " << current_timestamp << endl;
					continue;
				}
				// Need to check if current_running_process == NULL 
			}
			else
			{
				//cout << "next event is null - go to scheduler_handler" << endl;
			}	
			call_scheduler = false;
			//cout << "calling scheduler_handler()" << endl;	
			/*if(curr_state == Event::BLOCK)
			{
				curr_state = Event::READY;
				next_state = Event::RUNNING;
			}*/
			//if (current_running_process == NULL)
			//{
				current_running_process = scheduler_handler(
				args,
				run_queue,
				events,
				rands,
				current_timestamp,
				curr_state, 
				next_state);
				//cout << "return from scheduler_handler()" << endl;
			//}
		}
	}
	events.print_summary(args.scheduler_name);

	return 0;
}


