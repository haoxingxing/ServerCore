#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H
#include "domain.h"
#include "function.h"
#include <string>
#include <iostream>
class root_function : public root
{
public:
	root_function(const root* parent = nullptr);
	variable* execute(const std::vector<variable*>&) override = 0;
};
/*
 * The args are normal with "args"
 */
#define FUNCTION_DECLARATION(name)\
class name : public root_function { \
root* make_copy() override\
{\
	return new name;\
};\
variable* execute(const std::vector<variable*>& args) override;\
}
#define FUNCTION_DEFINITION(name) \
variable* name::execute(const std::vector<variable*>& args)
#define REG_FUNCTION this->member->insert

 /*
  * Using the macro to get the ptr with the type
  * Example:
  * std::cout << GETTYPEOF("string",root_string,arg)->access();
  * Obj:
  *	The dest type's dynamic type (string)
  * Dst:
  *	The dest type
  * Ptr:
  *	 The source ptr
  */
#define GETTYPEOF(Obj,Dst,Ptr) (((Ptr)->get()->what() == ((Obj)))?((Ptr)->get()->to<Dst>()) : ((Ptr)->get()->convert_type(Obj)->get()->to<Dst>()))
class root_void : public root
{
public:
	root_void(const root* parent = nullptr) :root("void", parent) { }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_void();
	};
};
class root_bool : public root
{
public:
	root_bool(const bool& a = false, const root* parent = nullptr) :root("bool", parent) { d = a; }
	bool& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<variable> override;
	root* make_copy() override
	{
		return new root_bool(d);
	};
private:
	bool d;
};
class root_char : public root
{
public:
	root_char(const char& a = 0, const root* parent = nullptr) :root("char", parent) { d = a; }
	char& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<variable> override;
	root* make_copy() override
	{
		return new root_char(d);
	};
private:
	char d;
};
class root_int : public root
{
public:
	root_int(const int& a = 0, const root* parent = nullptr) :root("int", parent) { d = a; }
	int& access() { return  d; }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_int(d);
	};
private:
	int d;
};

class root_string : public root
{
public:
	root_string(const std::string& a = "", const root* parent = nullptr) :root("string", parent) { d = a; }
	std::string& access() { return  d; }
	std::shared_ptr<variable> convert_type(const std::string& t) override;
	root* make_copy() override
	{
		return new root_string(d);
	};
private:
	std::string d;
};

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
#endif // BASIC_TYPES_H
