#include <base.h>

void BaseValidator::set_count(unsigned int count)
{
	_count = count;
}

unsigned int BaseValidator::get_count()
{
	return _count;
}

bool BaseValidator::is_valid_count(int count)
{
	return false;
}

