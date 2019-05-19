#ifndef CHAR_H
#define CHAR_H
#include "../root.h"

class root_char : public root
{
public:
	root_char(const char& a = 0, const root* parent = nullptr) :root("char", parent) { d = a; }
	char& access() { return  d; }
	std::unique_ptr<root> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_char(d);
	};
private:
	char d;
};
#endif // CHAR_H
