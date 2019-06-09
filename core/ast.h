﻿#ifndef AST_H
#define AST_H
#include <string>
#include <vector>

class ast
{
public:
	struct tree
	{
		std::vector<tree> args;
		std::string data;
	};
	static tree analysis(const std::vector<std::string>&);
	static std::vector<std::string> split(const std::string&);
	static std::string clean_str(std::string raw);
	static std::vector<std::string> merge(const std::vector<std::string>&, const std::string& de);
	static bool find_start_key(const std::string&);
	static bool find_end_key(const std::string&);
	static std::string dig(std::string& data,const char& start='(',const char& end=')');
};
#endif // AST_H
