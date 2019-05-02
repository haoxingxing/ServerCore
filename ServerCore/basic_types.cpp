#include "basic_types.h"
bool data_void::is_convertible_to(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return true;
	}
	_SWITCH_DEFAULT
		return false;
	_SWITCH_END
};
data_container* data_void::convert_type(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return new data_container("string", new data_string("void"));
	}
	_SWITCH_DEFAULT
		return new data_container();
	_SWITCH_END
}
data_container* data_int::convert_type(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return new data_container("string", new data_string(std::string(1, char(d))));
	}
	_SWITCH_DEFAULT
		return new data_container();
	_SWITCH_END
}
bool data_int::is_convertible_to(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return true;
	}
	_SWITCH_DEFAULT
		return false;
	_SWITCH_END
};