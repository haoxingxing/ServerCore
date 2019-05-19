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
		enum _type {
			exec, var, _if, _while
		}type;
	};
	static tree analysis(const std::vector<std::string>&);
	static std::vector<std::string> split(const std::string&);
	static std::string clean_str(std::string raw);
	static std::vector<std::string> merge(const std::vector<std::string>&, const std::string& de);
};
#endif // AST_H
