#include "basic_types.h"
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

data_function::data_function(const data* parent) : data("function", parent)
{
}
builtin::builtin() : data("builtin")
{
	reg_function("var", new data_container(new var));
	reg_function("echo", new data_container(new echo));
}