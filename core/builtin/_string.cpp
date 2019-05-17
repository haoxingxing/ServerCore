#include "_string.h"
#include "../variable.h"

std::shared_ptr<variable> root_string::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}