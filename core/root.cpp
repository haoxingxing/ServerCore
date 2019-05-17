#include "root.h"
#include "core.h"
#include "domain.h"

root::root(std::string type, const root* parent) : type(std::move(type))
{
	DEB(PRINT_POINTER(this));
	member = parent == nullptr ? [&]() {
		return new domain;
	}() :
		[&]() {
		is_member_own = false;
		return parent->member;
	}();
}
variable* root::access_member(const std::string& name)
{
	return member->get(name);
}
root::~root()
{
	DEB(PRINT_POINTER(this));
}
std::shared_ptr<variable> root::convert_type(const std::string&)
{
	return std::make_shared<variable>();
}