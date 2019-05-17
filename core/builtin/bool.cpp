#include "bool.h"
#include "int.h"
#include "_string.h"
#include "../variable.h"

auto root_bool::convert_type(const std::string& t)->std::shared_ptr<variable>
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<variable>(new root_string(d ? "true" : "false"));
	}
	SWITCH_CASE("int")
	{
		return std::make_shared<variable>(new root_int(d));
	}
	SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}