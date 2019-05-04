#include "basic_types.h"
std::shared_ptr<data_container> data_void::convert_type(const std::string& t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string("void"));
	}
	_SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(false));
	}
	_SWITCH_CASE("int")
	{
		return std::make_shared<data_container>(new data_int(0));
	}
	_SWITCH_DEFAULT
		return std::make_shared<data_container>();
	_SWITCH_END
}
auto data_bool::convert_type(const std::string& t)->std::shared_ptr<data_container>
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(d ? "true" : "false"));
	}
	_SWITCH_CASE("int")
	{
		return std::make_shared<data_container>(new data_int(d));
	}
	_SWITCH_DEFAULT
		return std::make_shared<data_container>();
	_SWITCH_END
}
std::shared_ptr<data_container> data_int::convert_type(const std::string & t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(std::to_string(d)));
	}
	_SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(d));
	}
	_SWITCH_CASE("char")
	{
		return std::make_shared<data_container>(new data_char(d));
	}
	_SWITCH_DEFAULT
		return std::make_shared<data_container>();
	_SWITCH_END
}
std::shared_ptr<data_container> data_char::convert_type(const std::string & t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(std::string(1, d)));
	}
	_SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(d));
	}
	_SWITCH_DEFAULT
		return std::make_shared<data_container>();
	_SWITCH_END
}
std::shared_ptr<data_container> data_string::convert_type(const std::string & t)
{
	_SWITCH_BEGIN(t)
		_SWITCH_DEFAULT
		return std::make_shared<data_container>();
	_SWITCH_END
}

data_function::data_function(const data * parent) : data("function", parent)
{
}
builtin::builtin() : data("builtin")
{
	reg_function("var", new data_container(new var));
	reg_function("echo", new data_container(new echo));
	reg_function("input", new data_container(new input));
}