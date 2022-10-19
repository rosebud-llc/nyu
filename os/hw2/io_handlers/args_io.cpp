#include <args_io.h>

#include <iostream> // cout, endl
#include <fstream>  // ifstream
#include <string.h> // strcmp, strlen

// getopt libs
#include <ctype.h>
#include <stdlib.h> // strtoul
#include <unistd.h>


vector<unsigned int> getRandomValues(const char* random_file)
{
	vector<unsigned int> rands;
	ifstream random_file_stream;
	random_file_stream.open(random_file);
	if(random_file_stream.is_open())
	{
		string line;
		bool skip_first_line = false; 
		while(getline(random_file_stream,line,'\n'))
		{
			char* rand_value = new char[line.length()+1];
			strcpy(rand_value,line.c_str());
			if(!skip_first_line)
			{
				unsigned int line_count 
					= (unsigned int)strtoul(rand_value,NULL,10);
				rands.reserve(line_count);
				skip_first_line = true;
				delete rand_value;
				continue;
			}
			rands.push_back(
				(unsigned int)strtoul(rand_value,NULL,10));
			delete rand_value;
		}
		random_file_stream.close();
	}
	else
	{
		cerr << "Failed to open ranndom file: " << random_file << endl; 
	}
	cout << "Total random values added to vector: " << rands.size() << endl;
	return rands;
}

void init_args(Args& args)
{
	args.trace_state_transition = false;  // -v
        args.trace_event_execution  = false;  // -t
        args.trace_event_queue      = false;  // -e
        args.trace_preemption       = false;  // -p
        // Scheduler Specifications
        args.scheduler_specification = 'F';    // -s where DEFAULT == First-Come, First-Served (FCFS)
        args.quantum = 0;
        args.maxprio = 4;  // DEFAULT == 4
        // Input Files
        args.input_file  = "";   // space delimited <unsigned int>'s "AC TC CB IO" per newline 
        args.random_file = "";   // first line is total line count; every subsequent line <unsigned int> 
}

unsigned int parse_scheduler_specification(const char* spec, Args& args)
{
	// F = FCFS, first-come, first-served
	// L = LCFS, last-come, last-served
	// S = SRTF, shortest remaining execution time
	//TODO: fix up the meaning of <num>:<maxprio>
	// R<num> = RR, round-robin
	// P<num>:<maxprio> = PRIO, round-robin
	// 	priority-level == quantum
	// 	(optional) max priority-level == maxprio
	// E<num>:<maxprio> = PREPRIO, round-robin 
	// 	priority-level == quantum
	// 	(optional) max priroty-level == maxprio
	
	// Parse scheduler specifications
	const char* valid_schedulers = "FLSRPE";
	char scheduler_type = '0';
	int quantum = -1;
	int maxprio = -1;
	sscanf(spec,"%c%d:%d",
		&scheduler_type,
		&quantum,
		&maxprio);
	
	// Validate scheduler specification
	if (strchr(valid_schedulers,
		scheduler_type) == NULL)
	{
		cerr << "ERROR: Invalid scheduler option provided: " << scheduler_type
			<< ". Please choose a valid scheduler." << endl;
		//TODO  print valid list of schedule options here		
		return 1;
	}
	else
	{
		args.scheduler_specification = scheduler_type;
	}
	
	// Validate quantum and maxprio, if necessary.
	if (scheduler_type == 'R' 
		|| scheduler_type == 'P' 
		|| scheduler_type == 'E')
	{
		if (quantum < 0)
		{
			cerr << "ERROR: Scheduler type " << scheduler_type 
				<< " requires positive quantum value." << endl;
			return 1;
		}
		args.quantum = (unsigned int)quantum;
		if (maxprio >= 0)
		{
			args.maxprio = (unsigned int)maxprio;	
		}
	}
	
	return 0;
}

void print_args(const Args& args)
{
	cout << "Args" << endl;
	cout << "\t-v: " << args.trace_state_transition << endl;
	cout << "\t-t: " << args.trace_event_execution << endl;
	cout << "\t-t: " << args.trace_event_queue << endl;
	cout << "\t-p: " << args.trace_preemption << endl;
	cout << "\t-s: " << args.scheduler_specification << endl;
	cout << "\t\tquantum: " << args.quantum << endl;
	cout << "\t\tmaxprio: " << args.maxprio << endl;
	cout << "\tinput_file: " << args.input_file << endl;
	cout << "\trandom_file: " << args.random_file << endl;
}

unsigned int get_args(int argc, char* argv[], Args& args)
{
	if (argc < 3)
	{
		cerr << "ERROR: Minimum two files required." << endl;
		return 1;
	}

	// Initialize args
	init_args(args);
	
	// Process option args
	int c;
	while ((c = getopt (argc, argv, "vteps:")) != -1)
	{
		switch(c)
		{
			case 'v':
				args.trace_state_transition = true;
				break;
			case 't':
				args.trace_event_execution = true;
				break;
			case 'e':
				args.trace_event_queue = true;
				break;
			case 'p':
				args.trace_preemption = true;
				break;
			case 's':
				args.scheduler_specification = true;
				if (parse_scheduler_specification(optarg,args))
				{
					return 1;
				}
				break;
			case '?':
				if (optopt == 's')
				{			
					cerr << "ERROR: Option -s requires an argument." << endl;
				}
				else
				{
					cerr << "ERROR: Unknown option: " << optopt << endl;
				}
				return 1;
			default:
				cerr << "ERROR: Unknown error occured parsing args." << endl;
				return 1;
		}
	}
	
	// Set input and random file
	int i = optind;
	if (i < argc) args.input_file = argv[i];
	else cerr << "ERROR: Failed to load input_file - too few arguments." << endl;
	if (++i < argc) args.random_file = argv[i];
	else cerr << "ERROR: FAiled to load rand_file - too few arguments." << endl;
	
	return 0;
}


