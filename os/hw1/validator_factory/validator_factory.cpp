#include <validator_factory.h>
#include <validators/definition.h>
#include <validators/use.h>
#include <validators/program.h>

bool ValidatorFactory::process(char* p_token) const
{
	BaseValidator* validator = this->FactoryMethod();
	bool result = validator->process(p_token);
	delete validator;
	return result;
}

BaseValidator::ValidatorType::validator_enum ValidatorFactory::get_validator_enum() const
{
	BaseValidator* validator = this->FactoryMethod();
	BaseValidator::ValidatorType::validator_enum result = validator->get_validator_enum();
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



