#ifndef INCLUDED_EVENTS_HEADER
#define INCLUDED_EVENTS_HEADER

#include <events/event.h>
#include <rands/rands.h>

#include <utility>  // pair
#include <fstream>  // is_open, close
#include <vector>
#include <string>
#include <list>
using namespace std;

class Events
{

public:
	Events(const char* input_file,
		const unsigned int maxprio,
		Rands& rands); 
	~Events();	

	// setters
	void pop_front_event();
	void add_event(Process*,
		unsigned int timestamp, // i.e. the event timestamp
		Event::EVENT_STATE curr_state,
		Event::EVENT_STATE next_state);
		
	// getters
	Event* get_front_event();
	unsigned int get_timestamp_when_cpu_free(unsigned int);

	// printers
	void print_events();
	void print_summary(string& scheduler_type);

private:
	// variables
	ifstream _process_stream;
	list<Event*> _events_list;
	vector<Process*> _completed_processes;
	
	// methods to initialzie Events
	Process* _get_process_from_stream(
		const unsigned int pid,
		const unsigned int maxprio,
		Rands& rands);
	void _init_events_list(
		const unsigned int maxprio,
		Rands& rands);
	void _init_completed_processes();	
	
	// methods to sort events and completed processes
	//void _sort_events(const unsigned int);
	//void _sort_completed_processes();
	//bool _compare_pids(Process*,Process*);
};

#endif
