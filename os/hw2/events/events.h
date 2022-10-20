#ifndef INCLUDED_EVENTS_HEADER
#define INCLUDED_EVENTS_HEADER

#include <events/event.h>

#include <utility>  // pair
#include <fstream>  // is_open, close
#include <vector>
#include <string>
#include <list>
using namespace std;

class Events
{

public:
	Events(const char* input_file); 
	~Events();	

	// setters
	void pop_front_event();
	void add_completed_process(Process*);
	
	// getters
	Event* get_front_event();

	// printers
	void print_summary(string& scheduler_type);

private:
	// variables
	ifstream _process_stream;
	list<Event*> _events_list;
	vector<Process*> _completed_processes;
	
	// methods to initialzie Events
	Process* _get_process_from_stream(const unsigned int pid);
	void _init_events_list();
	void _init_completed_processes();	
};

#endif
