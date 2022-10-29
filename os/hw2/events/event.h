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
                NONE=0,
		CREATED=1,
                READY=2,
                RUNNING=3,
                BLOCK=4,
		PREEMPT=5,
        };

	// Constructor
	Event(Process* process) :
		_prev_state(NONE),
		_curr_state(CREATED),
		_next_state(READY),
		_process(process), 
		_timestamp(process->get_arrival_time())
		{};

	Event(Process* process,
		EVENT_STATE curr_state,
		EVENT_STATE next_state,
		unsigned int timestamp) :
			_prev_state(NONE),
			_curr_state(curr_state),
			_next_state(next_state),
			_process(process),
			_timestamp(timestamp) {};

	// setters
	void set_prev_state(const EVENT_STATE);
	void set_curr_state(const EVENT_STATE);
	void set_next_state(const EVENT_STATE);
	void set_timestamp(unsigned int timestamp);       
 
	// getters
	EVENT_STATE get_prev_state();
	EVENT_STATE get_curr_state();
	EVENT_STATE get_next_state();
	static string get_event_state_str(const EVENT_STATE);
	Process* get_process() const;
	unsigned int get_timestamp();

	// printers
	void print_event_info();
	void print_event_summary(string& scheduler_type);		

private:
	EVENT_STATE _prev_state;
	EVENT_STATE _curr_state;
	EVENT_STATE _next_state;
	Process* _process;
	unsigned int _timestamp;		
	
};

#endif
