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

unsigned int Process::get_static_priority()
{
	return _static_priority;
}

unsigned int Process::get_dynamic_priority()
{
	return _dynamic_priority;
}

unsigned int Process::get_state_transition_timestamp()
{
	return _state_transition_timestamp;
}

unsigned int Process::get_elapsed_time()
{
	return _elapsed_time;
}

unsigned int Process::get_elapsed_block_time()
{
	return _elapsed_block_time;
}

bool Process::is_done()
{
	return (_elapsed_time >= _total_cpu_time);
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

void Process::set_static_priority(const unsigned int sp)
{
	_static_priority = sp;
}

void Process::set_dynamic_priority(const unsigned int dp)
{
	_dynamic_priority = dp;
}

void Process::set_state_transition_timestamp(const unsigned int stt)
{
	_state_transition_timestamp = stt;
}

void Process::set_elapsed_time(const unsigned int cpu_usage_time)
{
	unsigned int new_elapsed_time =
                _elapsed_time + cpu_usage_time;
        if (new_elapsed_time > _total_cpu_time)
        {
                _elapsed_time = _total_cpu_time;
        }
	else
	{
		_elapsed_time = new_elapsed_time;
	}
}

void Process::set_elapsed_block_time(const unsigned int block_time)
{
	_elapsed_block_time += block_time;
}
	
void Process::print_process_info()
{
	cout << "Process info:" << endl;
	cout << "\t_pid: " << _pid << endl;
	cout << "\t_arrival_time: " << _arrival_time << endl; 
	cout << "\t_total_cpu_time: " << _total_cpu_time << endl;
	cout << "\t_cpu_burst: " << _cpu_burst << endl;
	cout << "\t_io_burst: " << _io_burst << endl;
	cout << "\t_static_priority: " << _static_priority << endl;
	cout << "\t_dynamic_priority: " << _dynamic_priority << endl;
	cout << "\t_state_transition_timestamp: " << _state_transition_timestamp << endl;
	cout << "\t_elapsed_time: " << _elapsed_time << endl;
}	

void Process::print_process_summary(string& scheduler_type)
{
	printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n",
		_pid,
		_arrival_time,
		_total_cpu_time,
		_cpu_burst,
		_io_burst,
		_static_priority, // TODO: Static Priority (but only print if scheduler_type == PRO/PREPRIO
		_state_transition_timestamp, // TODO: Finishing Time
		_state_transition_timestamp - _arrival_time, // TODO: Turnaround Time
		_elapsed_block_time, // TODO: I/O Time
		0); // TODO: CPU Waiting Time - i.e., time in 'Ready' state
			// to calculate this i think you would need to update the timestamp of
			// every process in run_queue during scheduler_handler() which holds all processes
			// and would, by that point, have the latest timestamp	
}


