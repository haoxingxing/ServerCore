#include "builtin.h"
#include "../core.h"
#include "_string.h"
#include "../domain.h"
#include <iostream>

builtin::builtin() : root("builtin")
{
}
root* builtin::new_this()
{
	REG_FUNCTION("var", new variable(new var));
	REG_FUNCTION("echo", new variable(new echo));
	REG_FUNCTION("input", new variable(new input));
	return this;
}

FUNCTION_DEFINITION(builtin::var) {
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
FUNCTION_DEFINITION(builtin::echo) {	
	for (auto& arg : args)
	{
		std::cout << GET_TYPE("string", root_string, (arg->get()))->access();
	}
	return new variable;
}
FUNCTION_DEFINITION(builtin::input) {
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