#include <events/event.h>

#include <iostream>  // cout, endl


void Event::set_prev_state(const Event::EVENT_STATE es)
{
        _prev_state = es;
}

void Event::set_curr_state(const Event::EVENT_STATE es)
{
	_curr_state = es;
}

void Event::set_next_state(const Event::EVENT_STATE es)
{
	_next_state = es;
}

void Event::set_timestamp(unsigned int timestamp)
{
	_timestamp = timestamp;
}


Event::EVENT_STATE Event::get_prev_state()
{
        return _prev_state;
}

Event::EVENT_STATE Event::get_curr_state()
{
	return _curr_state;
}

Event::EVENT_STATE Event::get_next_state()
{
	return _next_state;
}

// static
string Event::get_event_state_str(const Event::EVENT_STATE es)
{
        switch(es)
        {
                case NONE:
			return "NONE";
			break;
		case CREATED:
                        return "CREATED";
                        break;
                case READY:
                        return "READY";
                        break;
                case RUNNING:
                        return "RUNNG";
                        break;
                case BLOCK:
                        return "BLOCK";
                        break;
                default:
                        cerr << "Failed to convert enum EVENT_STATE to string. Enum unknown: " << es << endl;
                        return "";
        }
}

Process* Event::get_process() const
{
	return _process;
}

unsigned int Event::get_timestamp()
{
	return _timestamp;
}

void Event::print_event_info()
{
        cout << "Event Info: " << endl;
        cout << "\t_prev_state: " << get_event_state_str(_prev_state) << endl;
	cout << "\t_curr_state: " << get_event_state_str(_curr_state) << endl;
	cout << "\t_next_state: " << get_event_state_str(_next_state) << endl;
}

void Event::print_event_summary(string& scheduler_type)
{
	_process->print_process_summary(scheduler_type);
}


