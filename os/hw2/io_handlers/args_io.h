#ifndef INCLUDED_ARGS_IO_HEADER
#define INCLUDED_ARGS_IO_HEADER

#include <vector>
#include <utility> //Pair
using namespace std;


vector<pair<const char*,const char*> > parseArgs(int argc, char* argv[]);
const char* getInputFileName(vector<pair<const char*,const char*> > args);

#endif
