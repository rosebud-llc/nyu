#include <linker.h>

#include <iostream> // I/O Stream
#include <stdlib.h> // strtoul
#include <queue>    // queue

#include <io_handlers/args_io.h>   // parseArgs, getInputFileName
#include <io_handlers/log_io.h>    // getLogPrefix
#include <io_handlers/file_io.h>   // loadFileStream

#include <validators/definition.h> // DefinitionValidator
#include <validators/use.h>        // UseValidator
#include <validators/program.h>    // ProgramValidator

#include <validator_factory/validator_factory.h> // ValidatorFactory

#include <tokenizer/tokenizer.h> // processFileStream

using namespace std;

struct ModuleValidator
{
	enum validator {definition,use,program};
	vector<int> ordered_validator_ids;
	queue<int> validator_queue;

} module;

void load_ordered_validator_ids()
{
	module.ordered_validator_ids.push_back(module.definition);
	module.ordered_validator_ids.push_back(module.use);
	module.ordered_validator_ids.push_back(module.program);
}

void enqueue_validator_id(ModuleValidator::validator validator_id)
{
	module.validator_queue.push(validator_id);
}

void reset_counter(unsigned int& counter, char* token)
{
	//TODO: return can be 0 or ULONG_MAX on error: https://cplusplus.com/reference/cstdlib/strtoul/
	//TODO: create unit test
	unsigned long ul_counter = strtoul(token,NULL,0);
	counter = (unsigned int)ul_counter;
}

int main(int argc, char* argv[])
{

	vector<pair<const char*,const char*> > args = parseArgs(argc,argv);
	const char* input_file_name = getInputFileName(args);
	ifstream input_file_stream;
	loadFileStream(input_file_name, input_file_stream);
	processFileStream(input_file_stream);

	// Test validator factory
	queue<ValidatorFactory*> myqueue;
	ValidatorFactory* def_validator = new CreateDefinitionValidator();
	myqueue.push(def_validator);
	ValidatorFactory* use_validator = new CreateUseValidator();
	myqueue.push(use_validator);
	ValidatorFactory* prog_validator = new CreateProgramValidator();
	myqueue.push(prog_validator);
	while(!myqueue.empty())
	{
		ValidatorFactory* validator = myqueue.front();
		validator->process();
		myqueue.pop();
	}
	return 0;
}
