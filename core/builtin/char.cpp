#include "char.h"
#include "_string.h"
#include "bool.h"
#include "void.h"

std::unique_ptr<root> root_char::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return _make_unique<root_string>(std::string(1, d));
	}
	SWITCH_CASE("bool")
	{
		return _make_unique<root_bool>(d);
	}
	SWITCH_DEFAULT
		return _make_unique<root_void>();
	SWITCH_END
}
