#ifndef BOOL_H
#define BOOL_H
#include "../root.h"
#include "../variable.h"
class root_bool : public root
{
public:
	root_bool(const bool& a = false, root* parent = nullptr) :root("bool", parent) { d = a; }
	bool& access() { return  d; }
	std::unique_ptr<root> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_bool(d);
	};
	root* new_this() override;
	FUNCTION_DECLARATION(negate);
	FUNCTION_DECLARATION(_and);
	FUNCTION_DECLARATION(_or);
private:
	bool d;
};
#endif // BOOL_H
