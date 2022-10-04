#ifndef INCLUDED_VALIDATOR_QUEUE_HEADER
#define INCLUDED_VALIDATOR_QUEUE_HEADER

#include <validator_data/validator_data.h>

#include <queue>
#include <utility> // pair
using namespace std;

queue<ValidatorData*> initialize_validator_queue();

void delete_validator_queue(queue<ValidatorData*> validators);

void reorder_validator_queue(queue<ValidatorData*>& validators);

#endif
