#ifndef INCLUDED_LOG_IO_HEADER
#define INCLUDED_LOG_IO_HEADER

#include <string>
using namespace std;


string getLogPrefix(const char* file, const char* function, int line);

#endif
