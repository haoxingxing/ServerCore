#include "root.h"
#include "core.h"
#include "domain.h"
#include "builtin/void.h"

root::root(std::string type, root* parent) : parent(parent), type(std::move(type))
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
	if (is_member_own)
		delete member;
	DEB(PRINT_POINTER(this));
}
std::unique_ptr<root> root::convert_type(const std::string&)
{
	return _make_unique<root_void>();
}