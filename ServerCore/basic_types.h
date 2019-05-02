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
#define DEFINE_FUNCTION_BEGIN(name)\
class name : public data_function { \
data_container* execute(std::vector<data_container*> args)
#define DEFINE_FUNCTION_END }

class data_void : public data
{
public:
	data_void(const data* parent = nullptr) :data("void", parent) { }
	std::shared_ptr<data_container> convert_type(const std::string& t);
	bool is_convertible_to(const std::string& t);
private:
};
class data_int : public data
{
public:
	data_int(const int& a = 0, const data* parent = nullptr) :data("int", parent) { d = a; }
	int& access() { return  d; }
	std::shared_ptr<data_container> convert_type(const std::string& t);
	bool is_convertible_to(const std::string& t);
private:
	int d;
};

class data_string : public data
{
public:
	data_string(const std::string& a = "", const data* parent = nullptr) :data("string", parent) { d = a; }
	std::string& access() { return  d; }
private:
	std::string d;
};

class builtin : public data
{
public:
	builtin();
	DEFINE_FUNCTION_BEGIN(var)
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
	DEFINE_FUNCTION_END;
	DEFINE_FUNCTION_BEGIN(echo)
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
	DEFINE_FUNCTION_END;
};
#endif // BASIC_TYPES_H
