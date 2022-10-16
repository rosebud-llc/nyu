#include <events/events.h>

int main()
{
	const char* input_file = "input_file.txt";
	Events events(input_file);	
	
	Process* process;
	while(process = events.get_event())
	{
		if(process == NULL)
		{		
			break;
		}
		process->print_process();
	}

	return 0;
}


