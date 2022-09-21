#ifndef INCLUDED_VALIDATOR_QUEUE_HEADER
#define INCLUDED_VALIDATOR_QUEUE_HEADER

//#include <validator_factory/validator_factory.h>
#include <validator_data/validator_data.h>

#include <queue>
#include <utility> // pair
using namespace std;

queue<ValidatorData*> initialize_validator_queue();

void delete_validator_queue(queue<ValidatorData*> validators);

void reorder_validator_queue(queue<ValidatorData*>& validators);

/*
 * VALIDATOR FACTORY CODE
 */
/*
queue<pair<ValidatorFactory*, unsigned int> > initialize_validator_queue();

void delete_validator_queue(queue<pair<ValidatorFactory*, unsigned int> > validators);

void reorder_validator_queue(queue<pair<ValidatorFactory*, unsigned int> >& validators);
*/

#endif
