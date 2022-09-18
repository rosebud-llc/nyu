#ifndef INCLUDE_BASE_HEADER
#define INCLUDE_BASE_HEADER

class BaseValidator
{
public:
	virtual ~BaseValidator(){};

	virtual bool process() const = 0;

	void set_count(unsigned int count);
	unsigned int get_count();
	bool is_valid_count(int count);

private:
	unsigned int _count;

};

#endif
