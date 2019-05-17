#ifndef BOOL_H
#define BOOL_H
#include "../root.h"
class root_bool : public root
{
public:
	root_bool(const bool& a = false, const root* parent = nullptr) :root("bool", parent) { d = a; }
	bool& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<variable> override;
	root* make_copy() override
	{
		return new root_bool(d);
	};
private:
	bool d;
};
#endif // BOOL_H
