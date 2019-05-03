#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H
#include "database.h"
#include "cmder.h"
#include <string>
#include <iostream>
class data_function : public data
{
public:
	data_function(const data* parent = nullptr);
	data_container* execute(std::vector<data_container*>) override = 0;
};
/*
 * The args are normal with "args"
 */
#define function_(name)\
class name : public data_function { \
data_container* execute(std::vector<data_container*> args)
#define _function }
#define reg_function this->member->insert
class data_void : public data
{
public:
	data_void(const data* parent = nullptr) :data("void", parent) { }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
private:
};
class data_bool : public data
{
public:
	data_bool(const bool& a = false, const data* parent = nullptr) :data("bool", parent) { d = a; }
	bool& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<data_container> override;

private:
	bool d;
};
class data_char : public data
{
public:
	data_char(const char& a = 0, const data* parent = nullptr) :data("char", parent) { d = a; }
	char& access() { return  d; }
	auto convert_type(const std::string& t)->std::shared_ptr<data_container> override;

private:
	char d;
};
class data_int : public data
{
public:
	data_int(const int& a = 0, const data* parent = nullptr) :data("int", parent) { d = a; }
	int& access() { return  d; }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
private:
	int d;
};

class data_string : public data
{
public:
	data_string(const std::string& a = "", const data* parent = nullptr) :data("string", parent) { d = a; }
	std::string& access() { return  d; }
	std::shared_ptr<data_container> convert_type(const std::string& t) override;
private:
	std::string d;
};

class builtin : public data
{
public:
	builtin();
	function_(var)
	{
		if (args.size() == 2)
		{
			args[0]->swap(args[1]);
		}
		else
		{
			ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
		}
		return new data_container;
	}
	_function;
	function_(echo)
	{
		for (auto& arg : args)
		{
			_SWITCH_BEGIN(Type(arg->get()))
				_SWITCH_CASE("null")
			{
				std::cout << "null";
			}
			_SWITCH_CASE("string")
				std::cout << arg->get()->to<data_string>()->access();
			_SWITCH_DEFAULT
				std::cout << arg->get()->convert_type("string")->get()->to<data_string>()->access();
			_SWITCH_END
		}
		return new data_container;
	}
	_function;
};
#endif // BASIC_TYPES_H
