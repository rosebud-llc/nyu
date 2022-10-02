#ifndef INCLUDED_TOKENIZER_HEADER
#define INCLUDED_TOKENIZER_HEADER

#include <string>
#include <fstream>
using namespace std;


unsigned int tokenizeLine(string& line, const char* delims, unsigned int counter);
void processFileStream(ifstream& input_file_stream);
void processFileStream(const char* input_file_name);

#endif
