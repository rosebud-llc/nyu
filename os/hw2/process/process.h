#ifndef INCLUDED_PROCESS_HEADER
#define INCLUDED_PROCESS_HEADER

#include <string>
using namespace std;


class Process
{

public:
	enum PROCESS_STATE
	{
        	CREATED=0,
        	READY=1,
        	RUNNING=2,
        	BLOCKED=3
	};


	Process(unsigned int at,
		unsigned int tc,
		unsigned int cb,
		unsigned int io) : 
			_arrival_time(at),
			_total_cpu_time(tc),
			_cpu_burst(cb),
			_io_burst(io) {};

	// getters
	PROCESS_STATE get_process_state();
	static string get_process_state_str(const PROCESS_STATE);
	unsigned int get_arrival_time();
	unsigned int get_total_cpu_time();
	unsigned int get_cpu_burst();
	unsigned int get_io_burst();	
	
	// setters
	void set_process_state(const PROCESS_STATE);
	void set_arrival_time(const unsigned int);
	void set_total_cpu_time(const unsigned int);
	void set_cpu_burst(const unsigned int);
	void set_io_burst(const unsigned int);
	
	void print_process();

private:
	PROCESS_STATE  _process_state;
	unsigned int _arrival_time; // Time at which a process arrives, is spanwed, or is created.
	unsigned int _total_cpu_time; // Total duration of CPU time this process requires
	unsigned int _cpu_burst; // Upper limit of compute demand
	unsigned int _io_burst; // Upper limit of io time

};

#endif
