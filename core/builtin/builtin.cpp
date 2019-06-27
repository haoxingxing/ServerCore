#include "builtin.h"
#include "../core.h"
#include "_string.h"
#include "../domain.h"
#include <iostream>
#include "s_iostream.h"

builtin::builtin(root* parent) : root("builtin", parent)
{
}
root* builtin::new_this()
{
	member->insert("var", new variable(new var));
	//member->insert("import", new variable(new _import));
	hd= new s_iostream(this);
	hd->new_this();
	return this;
}
builtin::~builtin()
{
	delete hd;
}

FUNCTION_DEFINITION(builtin::var) {
	if (args.size() == 2)
	{
		args[0]->copy_value(args[1]);
	}
	else
	{
		ERR_ARG_LEN(2);
	}
	return new variable;
}
//FUNCTION_DEFINITION(builtin::_import)
//{
//	for (auto& arg : args)
//	{
//		SWITCH_BEGIN(GET_TYPE("string", root_string, (arg->get()))->access())
//		SWITCH_CASE("iostream")
//		{
//			this->member->insert("iostream",new variable(new s_iostream(this)));
//		}
//		SWITCH_END
//	}
//	return new variable;
//}
