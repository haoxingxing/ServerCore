#include "variable.h"
#include "core.h"
#include "builtin/void.h"
variable::variable(root** d) : iscopy(true), d(d)
{
	DEB(PRINT_POINTER(this));
}
variable::variable(root* d) : iscopy(false)
{
	if (d == nullptr)
	{
		d = new root_void;
	}
	this->d = new root * (d);
	DEB(PRINT_POINTER(this));
}
variable::~variable()
{
	DEB(PRINT_POINTER(this));
	if (!iscopy)
	{
		if ((*d) != nullptr)
			(*d)->delete_this();
		*d = nullptr;
		delete d;
	}
}
void variable::copy_value(variable * s) const
{
	if ((*d) != nullptr)(*d)->delete_this();
	*d = nullptr;
	*(this->d) = (*(s->d))->make_copy()->new_this();
}
variable* variable::copy() const
{
	return new variable(d);
}