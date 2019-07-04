#ifndef AST_H
#define AST_H
#include <string>
#include <utility>
#include <vector>
class ast
{
public:
	struct tree
	{
		static int counter;
		~tree()
		{
			delete right;
			delete left;
			for (const auto& a : args)
			{
				delete a;
			}
			counter--;
		}
		tree* left;
		tree* right;
		std::vector<tree*> args;
		std::string key;
		enum _operation
		{
			EMPTY,
			DOT /* . */,
			NOT /* ! */,
			EXEC /* () */,
			MAKE /* = */,
			PLUS /* + */,
			MINUS /* - */,
			MULTIPLY /* * */,
			DIVISION /* / */,
			FN /* function */,
			IF /* if */,
			WHILE /* while */,
			MORE /* > */,
			LESS /* < */,
			MORE_EQUAL /* >= */,
			EQUAL /* == */,
			LESS_EQUAL /* <= */,
			NOT_EQUAL /* != */,
			AND /* && */,
			OR /* || */,
		}operation;

		tree(_operation __operation, std::string _key, std::vector<tree*> _args = {}, tree* _left = nullptr, tree* _right = nullptr);;
	};
	static tree* analysis(const std::vector<std::string>&);
	static tree* find_method(std::string raw);

	static std::vector<std::string> split(const std::string&);
	static bool find_start_key(const std::string&);
	static bool find_end_key(const std::string&);
};
#endif // AST_H
