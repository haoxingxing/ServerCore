#ifndef STRING_H
#define STRING_H
#include <string>
#include "../root.h"
#include "../variable.h"

class root_string : public root
{
public:
	root_string(const std::string& a = "", root* parent = nullptr) :root("string", parent) { d = a; }
	std::string& access() { return  d; }
	std::unique_ptr<root> convert_type(const std::string& t) override;
	root* make_copy() override { return new root_string(d); };
	root* new_this() override;
	FUNCTION_DECLARATION(equals);
	FUNCTION_DECLARATION(at);
	FUNCTION_DECLARATION(append);
	FUNCTION_DECLARATION(remove);
private:
	std::string d;
};
#endif // STRING_H
