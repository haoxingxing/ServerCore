#ifndef ROOT_H
#define ROOT_H
#include <string>
#include <memory>
#include <vector>
#include "log.h"
class variable;
class domain;
class root
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit root(std::string type,const root * parent = nullptr);
	virtual ~root();
	//Interface
	virtual root * new_this() { return this; };
	virtual void delete_this() { delete this; };
	virtual root* make_copy() = 0;
	virtual std::shared_ptr<variable> convert_type(const std::string&);
	virtual std::string what() { return type; };
	virtual variable* access_member(const std::string& name);
	virtual variable* execute(const std::vector<variable*>&) { return nullptr; };
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
	domain* member = nullptr;
private:
	bool is_member_own = true;
	std::string type;
};
#endif // ROOT_H
