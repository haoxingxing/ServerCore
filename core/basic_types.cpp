#include "basic_types.h"
#include "core.h"
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
std::shared_ptr<variable> root_int::convert_type(const std::string & t)
{
	SWITCH_BEGIN(t)
		SWITCH_CASE("string")
	{
		return std::make_shared<variable>(new root_string(std::to_string(d)));
	}
	SWITCH_CASE("bool")
	{
		return std::make_shared<variable>(new root_bool(d));
	}
	SWITCH_CASE("char")
	{
		return std::make_shared<variable>(new root_char(char(d)));
	}
	SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}
std::shared_ptr<variable> root_char::convert_type(const std::string & t)
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
std::shared_ptr<variable> root_string::convert_type(const std::string & t)
{
	SWITCH_BEGIN(t)
		SWITCH_DEFAULT
		return std::make_shared<variable>();
	SWITCH_END
}

root_function::root_function(const root * parent) : root("function", parent)
{
}
builtin::builtin() : root("builtin")
{
	REG_FUNCTION("var", new variable(new var));
	REG_FUNCTION("echo", new variable(new echo));
	REG_FUNCTION("input", new variable(new input));
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
		return new variable;
}
FUNCTION_DEFINITION(builtin::echo){
		for (auto& arg : args)
		{
			std::cout << GETTYPEOF("string",root_string,arg)->access();
		}
		return new variable;
}
FUNCTION_DEFINITION(builtin::input){
	std::string in;
	std::cin >> in;
	const auto x = new variable(new root_string(in));
	for (auto& arg : args)
	{
		arg->copy_value(x);		
	}
	delete x;
	return new variable;
}