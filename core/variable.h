#ifndef VARIABLE_H
#define VARIABLE_H
#include "root.h"
class variable
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit variable(root* * d);;
	explicit variable(root* d = nullptr);
	~variable();
	void copy_value(variable* s) const;
	variable* copy() const;;
	root* get() const { return *d; };
	explicit operator root* () const { return *d; };
private:
	root** d = nullptr;
	bool iscopy;
};
#endif // VARIABLE_H
