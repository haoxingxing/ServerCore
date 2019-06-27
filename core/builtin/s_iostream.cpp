#include "s_iostream.h"
#include <iostream>
#include "_string.h"
#include "../domain.h"
s_iostream::s_iostream(root* parent) : root("iostream", parent)
{
}
root* s_iostream::new_this()
{
	member->insert("cin", new variable(new cin));
	member->insert("cout", new variable(new cout));
	return this;
}

FUNCTION_DEFINITION(s_iostream::cin) {
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
FUNCTION_DEFINITION(s_iostream::cout) {
	for (auto& arg : args)
	{
		std::cout << GET_TYPE("string", root_string, (arg->get()))->access();
	}
	return new variable;
}
