#ifndef S_IOSTREAM_H
#define S_IOSTREAM_H
#include "../root.h"
#include "../variable.h"
class s_iostream : public root
{
public:
	s_iostream(root* parent);
	root* new_this() override;
	root* make_copy() override
	{
		return new s_iostream(parent);
	};
	FUNCTION_DECLARATION(cin);
	FUNCTION_DECLARATION(cout);
};
#endif // S_IOSTREAM_H
