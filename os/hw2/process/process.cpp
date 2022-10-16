#include <process.h>

#include <iostream> // cout, endl

Process::PROCESS_STATE Process::get_process_state()
{
	return _process_state;
}

// static
string Process::get_process_state_str(const Process::PROCESS_STATE ps)
{
	switch(ps)
	{
		case CREATED:
			return "CREATED";	
			break;		
		case READY:
			return "READY";
			break;
		case RUNNING:
			return "RUNNING";
			break;
		case BLOCKED:
			return "BLOCKED";
			break;
		default:
			cerr << "Failed to convert enum PROCESS_STATE to string. Enum unknown: " << ps << endl;
			return "";
	}
}

unsigned int Process::get_arrival_time()
{
	return _arrival_time;
}

unsigned int Process::get_total_cpu_time()
{
	return _total_cpu_time;
}

unsigned int Process::get_cpu_burst()
{
	return _cpu_burst;
}

unsigned int Process::get_io_burst()
{
	return _io_burst;
}


void Process::set_process_state(const Process::PROCESS_STATE ps)
{
	_process_state = ps;
}

void Process::set_arrival_time(const unsigned int at)
{
	_arrival_time = at;
}

void Process::set_total_cpu_time(const unsigned int tc)
{
	_total_cpu_time = tc;
}

void Process::set_cpu_burst(const unsigned int cb)
{
	_cpu_burst = cb;
}

void Process::set_io_burst(const unsigned int io)
{
	_io_burst = io;
}

void Process::print_process()
{
	cout << "Process info:" << endl;
	cout << "\t_process_state: " << Process::get_process_state_str(_process_state) << endl; 
	cout << "\t_arrival_time: " << _arrival_time << endl; 
	cout << "\t_total_cpu_time: " << _total_cpu_time << endl;
	cout << "\t_cpu_burst: " << _cpu_burst << endl;
	cout << "\t_io_burst: " << _io_burst << endl;
}	


