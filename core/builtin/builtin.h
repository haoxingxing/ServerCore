#ifndef BUILTIN_H
#define BUILTIN_H
#include "../root.h"
#include "../variable.h"
class builtin : public root
{
public:
	builtin(root* parent);
	root* new_this() override;
	root* make_copy() override
	{
		return new builtin(parent);
	};
	~builtin();
	FUNCTION_DECLARATION(var);
private:
	root* hd = nullptr;
};
#endif // BUILTIN_H
