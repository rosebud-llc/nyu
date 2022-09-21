#ifndef INCLUDED_VALIDATOR_HANDLER_HEADER
#define INCLUDED_VALIDATOR_HANDLER_HEADER

#include <validator_data/validator_data.h>
using namespace std;

unsigned int validator_handler(char* p_token, ValidatorData* validator, bool onlyEvaluateCount=false);

#endif
