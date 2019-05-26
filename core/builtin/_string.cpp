#include "_string.h"
#include "void.h"
#include "bool.h"
#include "../domain.h"
std::unique_ptr<root> root_string::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_DEFAULT
		return _make_unique<root_void>();
	SWITCH_END
}
root* root_string::new_this()
{
	REG_FUNCTION("equals", new variable(new equals(this)));
	return this;
}
FUNCTION_DEFINITION(root_string::equals)
{
	if (args.size() != 1)
		ERR_ARG_LEN(1);
	return new variable(new root_bool(GET_TYPE("string", root_string, parent)->d == GET_TYPE("string", root_string, args[0]->get())->d));
}