#include <validator_factory.h>
#include <validators/definition.h>
#include <validators/use.h>
#include <validators/program.h>


bool ValidatorFactory::process() const
{
	BaseValidator* validator = this->FactoryMethod();
	bool result = validator->process();
	delete validator;
	return result;
}

BaseValidator* CreateDefinitionValidator::FactoryMethod() const
{
	return new DefinitionValidator();
}


BaseValidator* CreateUseValidator::FactoryMethod() const
{
	return new UseValidator();
}


BaseValidator* CreateProgramValidator::FactoryMethod() const
{
	return new ProgramValidator();
}
