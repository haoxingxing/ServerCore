#include "bool.h"
#include "int.h"
#include "_string.h"
#include "void.h"
#include "../domain.h"
std::unique_ptr<root> root_bool::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return _make_unique<root_string>(d ? "true" : "false");
	}
	SWITCH_CASE("int")
	{
		return _make_unique<root_int>(d);
	}
	SWITCH_DEFAULT
		return _make_unique<root_void>();
	SWITCH_END
}
root* root_bool::new_this()
{
	member->insert("negate", new variable(new negate(this)));
	member->insert("and", new variable(new _and(this)));
	member->insert("or", new variable(new _or(this)));
	return this;
}
FUNCTION_DEFINITION(root_bool::negate)
{
	return new variable(new root_bool(!GET_TYPE("bool", root_bool, parent)->d));
}
FUNCTION_DEFINITION(root_bool::_and)
{
	if (args.size() != 1)
		ERR_ARG_LEN(1);
	return new variable(new root_bool(GET_TYPE("bool", root_bool, parent)->d && GET_TYPE("bool", root_bool, args[0]->get())->d));
}
FUNCTION_DEFINITION(root_bool::_or)
{
	if (args.size() != 1)
		ERR_ARG_LEN(1);
	return new variable(new root_bool(GET_TYPE("bool", root_bool, parent)->d || GET_TYPE("bool", root_bool, args[0]->get())->d));
}