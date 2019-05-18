#include "_string.h"
#include "void.h"

std::unique_ptr<root> root_string::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_DEFAULT
		return std::make_unique<root_void>();
	SWITCH_END
}
