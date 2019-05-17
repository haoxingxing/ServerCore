#ifndef BUILTIN_H
#define BUILTIN_H
#include "../root.h"
#include "../variable.h"
class builtin : public root
{
public:
	builtin();
	root* new_this() override;
	root* make_copy() override
	{
		return new builtin;
	};
	FUNCTION_DECLARATION(var);
	FUNCTION_DECLARATION(echo);
	FUNCTION_DECLARATION(input);
};
#endif // BUILTIN_H
