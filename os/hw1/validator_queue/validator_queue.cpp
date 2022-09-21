#include <validator_queue.h>

#include <iostream>

queue<ValidatorData*> initialize_validator_queue()
{
	queue<ValidatorData*> validators;
	// First: Definition
	cout << "Creating Definition Validator..." << endl;
	ValidatorData* definition_validator = new ValidatorData;
	initialize_validator_data(definition_validator,
			definition_validator->type.definition);
	validators.push(definition_validator);

	// Second: Use
	cout << "Creating Use Validator..." << endl;
	ValidatorData* use_validator = new ValidatorData;
	initialize_validator_data(use_validator,
			use_validator->type.use);
	validators.push(use_validator);

	// Third: Program
	cout << "Creating Program Validator..." << endl;
	ValidatorData* program_validator = new ValidatorData;
	initialize_validator_data(program_validator,
			program_validator->type.program);
	validators.push(program_validator);

	return validators;
}

void delete_validator_queue(queue<ValidatorData*> validators)
{
	while(!validators.empty())
	{
		ValidatorData* validator = validators.front();
		delete validator;
		validators.pop();
	}
}

void reorder_validator_queue(queue<ValidatorData*>& validators)
{
	validators.push(validators.front());
	validators.pop();
}

/*
 * VALIDATOR FACTORY CODE
 */
/*
queue<pair<ValidatorFactory*,unsigned int> > initialize_validator_queue()
{
	queue<pair<ValidatorFactory*, unsigned int> > validators;
	// First: Definition
	ValidatorFactory* def_validator = new CreateDefinitionValidator();
	validators.push(make_pair(def_validator,0));
	// Second: Use
	ValidatorFactory* use_validator = new CreateUseValidator();
	validators.push(make_pair(use_validator,0));
	// Third: Program
	ValidatorFactory* prog_validator = new CreateProgramValidator();
	validators.push(make_pair(prog_validator,0));

	return validators;
}

void delete_validator_queue(queue<pair<ValidatorFactory*, unsigned int> > validators)
{
	while(!validators.empty())
	{
		pair<ValidatorFactory*,unsigned int> validator = validators.front();
		delete validator.first;
		validators.pop();
	}
}

void reorder_validator_queue(queue<pair<ValidatorFactory*, unsigned int> >& validators)
{
	validators.push(validators.front());
	validators.pop();
}
*/
