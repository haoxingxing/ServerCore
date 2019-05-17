#ifndef STRING_H
#define STRING_H
#include <string>
#include "../root.h"
class root_string : public root
{
public:
	root_string(const std::string& a = "", const root* parent = nullptr) :root("string", parent) { d = a; }
	std::string& access() { return  d; }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_string(d);
	};
private:
	std::string d;
};
#endif // STRING_H
