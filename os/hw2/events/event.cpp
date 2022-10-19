#include <events/event.h>

#include <iostream>  // cout, endl


void Event::set_event_state(const Event::EVENT_STATE es)
{
        _event_state = es;
}

// private
Event::EVENT_STATE Event::get_event_state()
{
        return _event_state;
}

// private
string Event::_get_event_state_str()
{
        switch(_event_state)
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
                        cerr << "Failed to convert enum EVENT_STATE to string. Enum unknown: " << endl;
                        return "";
        }
}

Process* Event::get_process() const
{
	return _process;
}

void Event::print_event_info()
{
        cout << "Event Info: " << endl;
        cout << "\t_event_state: " << _get_event_state_str() << endl;
}

void Event::print_event_summary(string& scheduler_type)
{
	_process->print_process_summary(scheduler_type);
}


