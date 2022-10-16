#ifndef INCLUDED_FILE_IO_HEADER
#define INCLUDED_FILE_IO_HEADER

#include <queue_handler.h>
#include <fstream>
using namespace std;


void load_processes(const char* input_file_name,
	QueueHandler process_queue);

void load_randfile(const char* input_file_name,
	QueueHandler rand_queue);


#endif
