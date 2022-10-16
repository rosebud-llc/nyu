#ifndef INCLUDED_PROCESS_HEADER
#define INCLUDED_PROCESS_HEADER

using namespace std;

class Process
{

public:
	Process(unsigned int at,
		unsigned int tc,
		unsigned int cb,
		unsigned int io) : 
			_arrival_time(at),
			_total_cpu_time(tc),
			_cpu_burst(cb),
			_io_burst(io) {};

	// setters
	
	// getters	
	void print_process();

private:
	unsigned int _arrival_time; // Time at which a process arrives, is spanwed, or is created.
	unsigned int _total_cpu_time; // Total duration of CPU time this process requires
	unsigned int _cpu_burst; // Upper limit of compute demand
	unsigned int _io_burst; // Upper limit of io time

};

#endif
