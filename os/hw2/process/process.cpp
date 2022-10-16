#include <process.h>

#include <iostream> // cout, endl


void Process::print_process()
{
	cout << "Process info:" << endl;
	cout << "\t_arrival_time: " << _arrival_time << endl; 
	cout << "\t_total_cpu_time: " << _total_cpu_time << endl;
	cout << "\t_cpu_burst: " << _cpu_burst << endl;
	cout << "\t_io_burst: " << _io_burst << endl;
}	


