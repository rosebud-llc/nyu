#ifndef INCLUDED_PROCESS_HEADER
#define INCLUDED_PROCESS_HEADER

#include <string>
using namespace std;


class Process
{

public:

	Process(unsigned int pid,
		unsigned int at,
		unsigned int tc,
		unsigned int cb,
		unsigned int io,
		unsigned int sp) :
			_pid(pid), 
			_arrival_time(at),
			_total_cpu_time(tc),
			_cpu_burst(cb),
			_io_burst(io),
			_static_priority(sp),
			_dynamic_priority(sp-1), //TODO check if this is a good thing to do for all schedulers
			_state_transition_timestamp(at), //TODO correct to default to arrival time? so long as proccesses ordered correctly, this should be right
			_elapsed_time(0) {};

	// getters
	unsigned int get_pid();
	unsigned int get_arrival_time();
	unsigned int get_total_cpu_time();
	unsigned int get_cpu_burst();
	unsigned int get_io_burst();
	unsigned int get_static_priority();	
	unsigned int get_dynamic_priority();
	unsigned int get_state_transition_timestamp();
	unsigned int get_elapsed_time();
	unsigned int get_elapsed_block_time();
	bool is_done();
		
	// setters
	void set_pid(const unsigned int);
	void set_arrival_time(const unsigned int);
	void set_total_cpu_time(const unsigned int);
	void set_cpu_burst(const unsigned int);
	void set_io_burst(const unsigned int);
	void set_static_priority(const unsigned int);
	void set_dynamic_priority(const unsigned int);
	void set_state_transition_timestamp(const unsigned int);
	void set_elapsed_time(const unsigned int);	
	void set_elapsed_block_time(const unsigned int);

	// printers	
	void print_process_info();
	void print_process_summary(string& scheduler_type);

private:
	unsigned int _pid; // 0-based process ID incremented by 1 in ascending chronological _arrival_time order
	unsigned int _arrival_time; // Time at which a process arrives, is spanwed, or is created.
	unsigned int _total_cpu_time; // Total duration of CPU time this process requires
	unsigned int _cpu_burst; // Upper limit of compute demand
	unsigned int _io_burst; // Upper limit of io time
	unsigned int _static_priority; // Set using Rands(rfile) - only has impact on PRIO/PREPRIO schedulers
	unsigned int _dynamic_priority; // Priorty defined as value in range of [0...(_static_priority-1)]
	unsigned int _state_transition_timestamp; // Timestamp at which state or process was updated
	unsigned int _elapsed_time; // Amount of time process has used CPU
	unsigned int _elapsed_block_time; // Amount of time in block state
};

#endif
