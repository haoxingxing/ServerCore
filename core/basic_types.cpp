#include "basic_types.h"
std::shared_ptr<data_container> data_void::convert_type(const std::string& t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string("void"));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(false));
	}
	SWITCH_CASE("int")
	{
		return std::make_shared<data_container>(new data_int(0));
	}
	SWITCH_DEFAULT
		return std::make_shared<data_container>();
	SWITCH_END
}

auto data_bool::convert_type(const std::string& t)->std::shared_ptr<data_container>
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(d ? "true" : "false"));
	}
	SWITCH_CASE("int")
	{
		return std::make_shared<data_container>(new data_int(d));
	}
	SWITCH_DEFAULT
		return std::make_shared<data_container>();
	SWITCH_END
}
std::shared_ptr<data_container> data_int::convert_type(const std::string & t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(std::to_string(d)));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(d));
	}
	SWITCH_CASE("char")
	{
		return std::make_shared<data_container>(new data_char(char(d)));
	}
	SWITCH_DEFAULT
		return std::make_shared<data_container>();
	SWITCH_END
}
std::shared_ptr<data_container> data_char::convert_type(const std::string & t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<data_container>(new data_string(std::string(1, d)));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<data_container>(new data_bool(d));
	}
	SWITCH_DEFAULT
		return std::make_shared<data_container>();
	SWITCH_END
}
std::shared_ptr<data_container> data_string::convert_type(const std::string & t)
{
	SWITCH_BEGIN(t)
		SWITCH_DEFAULT
		return std::make_shared<data_container>();
	SWITCH_END
}

data_function::data_function(const data * parent) : data("function", parent)
{
}
builtin::builtin() : data("builtin")
{
	REG_FUNCTION("var", new data_container(new var));
	REG_FUNCTION("echo", new data_container(new echo));
	REG_FUNCTION("input", new data_container(new input));
}


FUNCTION_DEFINITION(builtin::var){
		if (args.size() == 2)
		{
			args[0]->copy_value(args[1]);
		}
		else
		{
			ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
		}
		return new data_container;
}
FUNCTION_DEFINITION(builtin::echo){
		for (auto& arg : args)
		{
			std::cout << GETTYPEOF("string",data_string,arg)->access();
		}
		return new data_container;
}
FUNCTION_DEFINITION(builtin::input){
	std::string in;
	std::cin >> in;
	const auto x = new data_container(new data_string(in));
	for (auto& arg : args)
	{
		arg->copy_value(x);		
	}
	delete x;
	return new data_container;
}