#ifndef AST_H
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
		enum type {
			exec, var, _if, _while
		};
	};
	static tree analysis(const std::vector<std::string>&);
	static std::vector<std::string> split(const std::string&);
	static std::string clean_str(std::string raw);
	static std::vector<std::string> split_arg(const std::string&);
};
#endif // AST_H
