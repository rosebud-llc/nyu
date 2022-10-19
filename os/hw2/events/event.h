#ifndef INCLUDED_EVENT_HEADER
#define INCLUDED_EVENT_HEADER

#include <process/process.h>

#include <string>
using namespace std;

class Event
{

public:
        enum EVENT_STATE
        {
                CREATED=0,
                READY=1,
                RUNNING=2,
                BLOCKED=3
        };

	// Constructor
	Event(Process* process) : 
		_event_state(CREATED),
		_process(process), 
		_timestamp(process->get_arrival_time())
		{};

	// setters
	void set_event_state(const EVENT_STATE);
        
	// getters
	EVENT_STATE get_event_state();
	Process* get_process() const;

	// printers
	void print_event_info();
	void print_event_summary(string& scheduler_type);		

private:
	EVENT_STATE _event_state;
	Process* _process;
	unsigned int _timestamp;		
	
        string _get_event_state_str();
};

#endif
