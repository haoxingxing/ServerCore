#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H
#include <iostream>
#include <string>
class log {
public:
	enum log_level
	{
		NONE,
		NOTICE,
		WARN,
		ERR
	};
	static void print(log_level,const std::string &info,bool t = true);
	static bool iscolored;
};

#endif
