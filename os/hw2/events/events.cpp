#include <events.h>

#include <iostream> // cout, endl
#include <sstream> 
#include <string>   // getline
#include <string.h> //strtok
#include <vector>   // push_back
#include <stdlib.h> // strtoul
#include <iomanip> // setfill, setw

// Constructor
Events::Events(const char* input_file) 
{
	if (input_file != NULL
		&& strlen(input_file) > 0)
	{
		_process_stream.open(input_file);
		_init_events_list();
		_init_completed_processes();
	}
	else
	{
		cerr << "Failed to open file: " << input_file << endl;
	}
}

// Destructor
Events::~Events()
{
	if(_process_stream.is_open())
	{
		_process_stream.close();
	}
	else
	{
		cerr << "Failed to close Events stream." << endl;
	}
}

/*
 * Open file stream. 
 * Read one line delimited by newline. 
 * Convert line to c_string.
 * Tokenize by whitespace and store in vector
 * Initialize Process with values from vector
 * 
 * &return: pointer to Process, NULL on error
 */
// private
Process* Events::_get_process_from_stream(const unsigned int pid)
{
	Process* process = NULL;

	if(_process_stream.is_open())	
	{	
		// Read event from events stream
		string line;
		getline(_process_stream, line, '\n');
		
		// Return NULL if end of file reached.
		if(_process_stream.eof())       
        	{                               
                	return process; 
		}
		cout << "LINE: " << line << endl;
		
		// Create new c_string from line
		char* c_string = new char [line.length()+1];
        	strcpy(c_string,line.c_str());
		
		// Tokenize line on whitespace and store in vector
		vector<unsigned int> tokens;
		static const char* delims = " \t";
		char* token = strtok(c_string,delims);
		while (token != NULL)
		{
			tokens.push_back( 
				(unsigned int)strtoul(
					token,
					NULL,
					10) );	
			token = strtok(NULL,delims);
		}
		
		// Delete c_string
		delete c_string;		

		// Create process for event
		static unsigned int num_process_inputs = 4;
		if (tokens.size() >= num_process_inputs)
		{
			process = new Process(pid,  // PID 
					tokens[0],  // Arrival Time							
					tokens[1],  // Total CPU Time
					tokens[2],  // CPU Burst
					tokens[3]); // IO Burst
		}
		else
		{
			cerr << "Failed to create Process from event stream. Number of process inputs insufficient." << endl;
		}
	}
	else
	{
		cerr << "Failed to create Proccess from event stream. Events stream is not open." << endl;
	}
	return process;
}

//private
void Events::_init_completed_processes()
{
	if(_events_list.size() < _completed_processes.max_size())
	{
		_completed_processes.reserve(_events_list.size());
	}
}

// private
void Events::_init_events_list()
{
	unsigned int pid = -1; // pre-increment in while lopp ensures 0-based pid
	Process* process;
        while(process = _get_process_from_stream(++pid))
        {
                if(process == NULL)
                {               
                        break;
                }
                process->print_process_info();
		Event* event = new Event(process);
		_events_list.push_back(event);
	}
	cout << "Total number of processes created: " << _events_list.size() << endl;
}


Event* Events::get_front_event()
{
	if (_events_list.empty())
	{
		return NULL;
	}
	else
	{
		return _events_list.front();
	}
}

void Events::pop_front_event()
{
	if (!_events_list.empty())
	{
		_events_list.pop_front();
	}
	else
	{
		cerr << "Failed to pop front event because _events_list is empty." << endl;
	}
}	

void Events::add_completed_process(Process* process)
{
	_completed_processes.push_back(process);
}

void Events::print_summary(string& scheduler_type)
{
	//TODO create char->string (i.e. F->FCFS) handler in args and save to args so you can pass as string parameter here 
	cout << scheduler_type << endl;
	vector<Process*>::const_iterator it = _completed_processes.begin();
	for(; it != _completed_processes.end(); ++it)
	{
		(*it)->print_process_summary(scheduler_type);
	}
	//TODO collect summary stats from each process and print here
	printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n",
		0, //TODO: Finishing time of last event (i.e. last process finished) 
		0.0, //TODO: CPU Utilization
		0.0, //TODO: IO utilization
		0.0, //TODO: Avg turnaround time
		0.0, //TODO: Avg CPU waiting time
		0.0); //TODO: Throughput of number of processes per 100 time units
}

void Events::add_event(Process* process,
            unsigned int cpu_usage_time, // i.e. the random value. //TODO is this where we should updated elapsed time? or only when process is in RUNNING state?
            unsigned int timestamp, // i.e. the event timestamp
            Event::EVENT_STATE curr_state,
            Event::EVENT_STATE next_state)
{
	// First, set process's elapsed time
	// TODO should this happen only when transition to RUNNING... not every event
	process->set_elapsed_time(cpu_usage_time);
	cout << "Elapsed time: " << process->get_elapsed_time() << endl;
	// Second, if process completed, mark it done, otherwise, create next Event
	unsigned int new_timestamp = timestamp + cpu_usage_time; // it's not always cpu_usage_time, it could be io time for blocking
	if (process->get_elapsed_time() >= process->get_total_cpu_time())
	{
		_completed_processes.push_back(process);
	}
	else
	{
		Event* event = new Event(process, curr_state, next_state, new_timestamp);
		_events_list.push_front(event);
		//^this needs to be a private function that properly sorts newly added events
	}
}


