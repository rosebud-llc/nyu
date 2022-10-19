#include <process.h>

#include <iostream> // cout, endl
#include <stdio.h>  // printf

unsigned int Process::get_pid()
{
	return _pid;
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


void Process::set_pid(const unsigned int pid)
{
	_pid = pid;
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

void Process::print_process_info()
{
	cout << "Process info:" << endl;
	cout << "\t_pid: " << _pid << endl;
	cout << "\t_arrival_time: " << _arrival_time << endl; 
	cout << "\t_total_cpu_time: " << _total_cpu_time << endl;
	cout << "\t_cpu_burst: " << _cpu_burst << endl;
	cout << "\t_io_burst: " << _io_burst << endl;
}	

void Process::print_process_summary(string& scheduler_type)
{
	printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n",
		_pid,
		_arrival_time,
		_total_cpu_time,
		_cpu_burst,
		_io_burst,
		0, // TODO: Static Priority (but only print if scheduler_type == PRO/PREPRIO
		0, // TODO: Finishing Time
		0, // TODO: Turnaround Time
		0, // TODO: I/O Time
		0); // TODO: CPU Waiting Time	
}


