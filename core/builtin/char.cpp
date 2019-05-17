#include "char.h"
#include "_string.h"
#include "bool.h"
#include "../variable.h"

std::shared_ptr<variable> root_char::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<variable>(new root_string(std::string(1, d)));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<variable>(new root_bool(d));
	}
	SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}