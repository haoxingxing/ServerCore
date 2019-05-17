#include "void.h"
#include "bool.h"
#include "int.h"
#include "_string.h"
#include "../variable.h"
std::shared_ptr<variable> root_void::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<variable>(new root_string("void"));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<variable>(new root_bool(false));
	}
	SWITCH_CASE("int")
	{
		return std::make_shared<variable>(new root_int(0));
	}
	SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}