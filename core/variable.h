#ifndef VARIABLE_H
#define VARIABLE_H
#include "root.h"
#include "core.h"
class variable
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit variable(root * *d);;
	explicit variable(root* d = nullptr);
	~variable();
	void copy_value(variable* s) const;
	variable* copy() const;;
	root* get() const { return *d; };
	explicit operator root* () const { return *d; };
	bool iscopy;
private:
	root** d = nullptr;
};
class root_function : public root
{
public:
	root_function(root* parent = nullptr);
	variable* execute(const std::vector<variable*>&) override = 0;
};
/*
 * The args are normal with "args"
 */
#define FUNCTION_DECLARATION(name)\
class name : public root_function { \
public:\
name(root* parent = nullptr):root_function(parent){}\
root* make_copy() override\
{\
	return new name;\
}; \
variable* execute(const std::vector<variable*>& args) override; \
}
#define FUNCTION_DEFINITION(name) \
variable* name::execute(const std::vector<variable*>& args)
#define REG_FUNCTION this->member->insert

#define ERR_ARG_LEN(num) ERR(TS_ID_24 #num TS_ID_25 TS_ID_26);

#endif // VARIABLE_H
