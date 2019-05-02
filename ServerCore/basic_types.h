#include "database.h"
#include <string>
class data_void : public data
{
public:
	data_void() :data("void") { }
	data_container* convert_type(const std::string& t);
	bool is_convertible_to(const std::string& t);
private:
};
class data_int : public data
{
public:
	data_int(const int& a = 0) :data("int") { d = a; }
	int& access() { return  d; }
	data_container* convert_type(const std::string& t);
	bool is_convertible_to(const std::string& t);
private:
	int d;
};

class data_string : public data
{
public:
	data_string(const std::string& a = "") :data("string") { d = a; }
	std::string& access() { return  d; }
private:
	std::string d;
};
