#ifndef AST_H
#define AST_H
#include <list>
#include <string>
#include <vector>

class ast
{
public:
	struct tree
	{
		std::list<tree> args;
		std::string data;
		enum type {
			exec,var,_if,_while
		};
	};
	tree analysis(const std::vector<std::string>&);
	static std::vector<std::string> split(const std::string&);
};
#endif // AST_H
