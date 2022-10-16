#ifndef INCLUDED_EVENTS_HEADER
#define INCLUDED_EVENTS_HEADER

#include <process/process.h>

#include <string.h> // strlen
#include <fstream>  // is_open, close
using namespace std;

class Events
{

public:
	Events(const char* input_file); 
	~Events();

	Process* get_event();	

private:
	ifstream _events;
};

#endif
