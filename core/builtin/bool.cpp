#include "bool.h"
#include "int.h"
#include "_string.h"
#include "void.h"

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
