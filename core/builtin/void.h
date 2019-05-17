#ifndef VOID_H
#define VOID_H
#include "../root.h"
class root_void : public root
{
public:
	root_void(const root* parent = nullptr) :root("void", parent) { }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_void();
	};
};
#endif // VOID_H
