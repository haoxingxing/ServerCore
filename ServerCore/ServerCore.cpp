// ServerCore.cpp: 定义应用程序的入口点。
//

#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "database.h"
#include <iostream>
using namespace std;

int main()
{
	std::string a = _database::map_to_str(std::map<std::string, _data>({
		std::make_pair("int_test",_data(2333)),
		std::make_pair("char_test",_data("str")),
		std::make_pair("string_test",_data("str")),
		std::make_pair("true",_data(true)),
		std::make_pair("false",_data(false)),
		}));

	cout << a << endl;
	cout << _database::map_to_str(_database::str_to_map(a));
	return 0;
}