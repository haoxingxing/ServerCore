#include "bool.h"
#include "int.h"
#include "_string.h"
#include "void.h"

std::unique_ptr<root> root_bool::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_unique<root_string>(d ? "true" : "false");
	}
	SWITCH_CASE("int")
	{
		return std::make_unique<root_int>(d);
	}
	SWITCH_DEFAULT
		return std::make_unique<root_void>();
	SWITCH_END
}
