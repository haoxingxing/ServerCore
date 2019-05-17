#pragma once
#include "database.h"
#include "cmder.h"
#include <string>
#include <iostream>
class data_function : public data
{
public:
	data_function(const data* parent = nullptr);
	data_container* execute(const std::vector<data_container*>&) override = 0;
};
/*
 * The args are normal with "args"
 */
#define FUNCTION_DECLARATION(name)\
class name : public data_function { \
data* make_copy() override\
{\
	return new name;\
};\
data_container* execute(const std::vector<data_container*>& args) override;\
}
#define FUNCTION_DEFINITION(name) \
data_container* name::execute(const std::vector<data_container*>& args)
#define REG_FUNCTION this->member->insert

/*
 * Using the macro to get the ptr with the type
 * Example:
 * std::cout << GETTYPEOF("string",data_string,arg)->access();
 * Obj:
 *	The dest type's dynamic type (string)
 * Dst:
 *	The dest type
 * Ptr:
 *	 The source ptr
 */
#define GETTYPEOF(Obj,Dst,Ptr) (((Ptr)->get()->what() == ((Obj)))?((Ptr)->get()->to<Dst>()) : ((Ptr)->get()->convert_type(Obj)->get()->to<Dst>()))
class data_void : public data
{
public:
	data_void(const data* parent = nullptr) :data("void", parent) { }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
	data* make_copy() override
	{
		return new data_void();
	};
};
class data_bool : public data
{
public:
	data_bool(const bool& a = false, const data* parent = nullptr) :data("bool", parent) { d = a; }
	bool& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<data_container> override;
	data* make_copy() override
	{
		return new data_bool(d);
	};
private:
	bool d;
};
class data_char : public data
{
public:
	data_char(const char& a = 0, const data* parent = nullptr) :data("char", parent) { d = a; }
	char& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<data_container> override;
	data* make_copy() override
	{
		return new data_char(d);
	};
private:
	char d;
};
class data_int : public data
{
public:
	data_int(const int& a = 0, const data* parent = nullptr) :data("int", parent) { d = a; }
	int& access() { return  d; }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
	data* make_copy() override
	{
		return new data_int(d);
	};
private:
	int d;
};

class data_string : public data
{
public:
	data_string(const std::string& a = "", const data* parent = nullptr) :data("string", parent) { d = a; }
	std::string& access() { return  d; }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
	data* make_copy() override
	{
		return new data_string(d);
	};
private:
	std::string d;
};

class builtin : public data
{
public:
	builtin();
	data* make_copy() override
	{
		return new builtin;
	};
	FUNCTION_DECLARATION(var);
	FUNCTION_DECLARATION(echo);
	FUNCTION_DECLARATION(input);
};