#ifndef INCLUDED_VALIDATOR_FACTORY_HEADER
#define INCLUDED_VALIDATOR_FACTORY_HEADER

#include <validators/base.h> // BaseValidator
using namespace std;

class ValidatorFactory
{
public:
	virtual ~ValidatorFactory(){};
	virtual BaseValidator* FactoryMethod() const = 0;

	bool process() const;
};

class CreateDefinitionValidator: public ValidatorFactory
{
public:
	BaseValidator* FactoryMethod() const;
};

class CreateUseValidator: public ValidatorFactory
{
public:
	BaseValidator* FactoryMethod() const;
};

class CreateProgramValidator: public ValidatorFactory
{
public:
	BaseValidator* FactoryMethod() const;
};

#endif
