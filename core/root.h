#ifndef ROOT_H
#define ROOT_H
#include <string>
#include <memory>
#include <vector>
#include "log.h"
template<typename T, typename... Args>
std::unique_ptr<T> _make_unique(Args&& ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
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
	virtual std::unique_ptr<root> convert_type(const std::string&);
	virtual std::string what() { return type; };
	virtual variable* access_member(const std::string& name);
	virtual variable* execute(const std::vector<variable*>&) { return nullptr; };
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
protected:
	domain* member = nullptr;
	const root* parent = nullptr;
private:
	bool is_member_own = true;
	std::string type;
};

/*
 * Using the macro to get the ptr with the type
 * Example:
 * std::cout << GET_TYPE("string",root_string,arg)->access();
 * Obj:
 *	The dest type's dynamic type (string)
 * Dst:
 *	The dest type
 * Ptr:
 *	 The source ptr
 */
#define GET_TYPE(Obj,Dst,Ptr) (((Ptr)->what() == ((Obj)))?((Ptr)->to<Dst>()) : ((Ptr)->convert_type(Obj)->to<Dst>()))
 /*
  * Use the macro to check if the type is correct
  */
#define CHECK_TYPE(Obj,Ptr) ((Ptr)->what() == ((Obj)))
#endif // ROOT_H
