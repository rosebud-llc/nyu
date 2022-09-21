#include <linker.h>

#include <io_handlers/args_io.h>   // parseArgs, getInputFileName
#include <io_handlers/file_io.h>   // loadFileStream
#include <tokenizer/tokenizer.h> // processFileStream

using namespace std;

int main(int argc, char* argv[])
{
	vector<pair<const char*,const char*> > args = parseArgs(argc,argv);
	const char* input_file_name = getInputFileName(args);
	ifstream input_file_stream;
	loadFileStream(input_file_name, input_file_stream);
	processFileStream(input_file_stream); //TODO this needs to return a symbol_table for next run?
	return 0;
}
