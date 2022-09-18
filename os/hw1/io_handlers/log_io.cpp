#include <log_io.h>

#include <sstream>


string getLogPrefix(const char* file, const char* function, int line)
{
	stringstream ss;
	ss << file << "::" << function << "::" << line << "::";
	return ss.str();
}
