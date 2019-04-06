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
	_data d;
	std::string a = _database::create_database_string();
	d.setValue("Hello World");
	_database::str_insert(a, "string", d);
	d.setValue(233);
	_database::str_insert(a, "int", d);
	d.setValue(true);
	_database::str_insert(a, "bool", d);
	d.clearValue();
	_database::str_insert(a, "void", d);
	cout << a;
	return 0;
}