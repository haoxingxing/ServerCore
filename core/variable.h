#ifndef VARIABLE_H
#define VARIABLE_H
#include "root.h"
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
private:
	root** d = nullptr;
	bool iscopy;
};
class root_function : public root
{
public:
	root_function(const root* parent = nullptr);
	variable* execute(const std::vector<variable*>&) override = 0;
};
/*
 * The args are normal with "args"
 */
#define FUNCTION_DECLARATION(name)\
class name : public root_function { \
root* make_copy() override\
{\
	return new name;\
};\
variable* execute(const std::vector<variable*>& args) override;\
}
#define FUNCTION_DEFINITION(name) \
variable* name::execute(const std::vector<variable*>& args)
#define REG_FUNCTION this->member->insert

 /*
  * Using the macro to get the ptr with the type
  * Example:
  * std::cout << GETTYPEOF("string",root_string,arg)->access();
  * Obj:
  *	The dest type's dynamic type (string)
  * Dst:
  *	The dest type
  * Ptr:
  *	 The source ptr
  */
#define GETTYPEOF(Obj,Dst,Ptr) (((Ptr)->get()->what() == ((Obj)))?((Ptr)->get()->to<Dst>()) : ((Ptr)->get()->convert_type(Obj)->get()->to<Dst>()))

#endif // VARIABLE_H
