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
std::shared_ptr<data_container> data_void::convert_type(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::shared_ptr<data_container>(new data_container(new data_string("void")));
	}
	_SWITCH_DEFAULT
		return std::shared_ptr<data_container>(new data_container());
	_SWITCH_END
}
std::shared_ptr<data_container> data_int::convert_type(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::shared_ptr<data_container>(new data_container(new data_string(std::string(1, char(d)))));
	}
	_SWITCH_DEFAULT
		return std::shared_ptr<data_container>(new data_container());
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

data_function::data_function(const data* parent) : data("function", parent)
{
}
builtin::builtin() : data("builtin")
{
	member->insert("var", new data_container(new var));
	member->insert("echo", new data_container(new echo));
}