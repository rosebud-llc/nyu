#include <io_handlers/args_io.h>
#include <events/events.h>


int main(int argc, char* argv[])
{
	// Parse args
        vector<pair<const char*,const char*> > args = parseArgs(argc,argv);
        const char* input_file = getInputFileName(args);
	
	// Create events stream
	Events events(input_file);	
	
	// Create processes from events stream
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


