#ifndef INT_H
#define INT_H
#include "../root.h"
class root_int : public root
{
public:
	root_int(const int& a = 0, const root* parent = nullptr) :root("int", parent) { d = a; }
	int& access() { return  d; }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_int(d);
	};
private:
	int d;
};
#endif // INT_H
