#ifndef INT_H
#define INT_H
#include "../root.h"
#include "../variable.h"

class root_int : public root
{
public:
	root_int(const int& a = 0, root * parent = nullptr) :root("int", parent) { d = a; }
	int& access() { return  d; }
	std::unique_ptr<root> convert_type(const std::string& t) override;
	root* make_copy() override { return new root_int(d); };
	root* new_this() override;
	FUNCTION_DECLARATION(plus);
	FUNCTION_DECLARATION(less);
	FUNCTION_DECLARATION(more);
	FUNCTION_DECLARATION(more_equals);
	FUNCTION_DECLARATION(less_equals);
	FUNCTION_DECLARATION(equals);
	FUNCTION_DECLARATION(multiply);
	FUNCTION_DECLARATION(division);
	FUNCTION_DECLARATION(minus);
private:
	int d;
};
#endif // INT_H
