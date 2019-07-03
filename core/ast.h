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
		~tree()
		{
			delete right;
			delete left;
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
			EQUAL /* = */,
			PLUS /* + */,
			MINUS /* - */,
			CHEN /* * */,
			CHU /* / */
		}operation;

		tree(_operation __operation, std::string _key, std::vector<tree*> _args = {}, tree* _left = nullptr, tree* _right = nullptr) :
			args(_args), left(_left), right(_right), key(std::move(_key)), operation(std::move(__operation))
		{};
	};
	static tree* analysis(const std::vector<std::string>&);
	static tree* find_method(std::string& raw);

	static std::vector<std::string> split(const std::string&);
	static bool find_start_key(const std::string&);
	static bool find_end_key(const std::string&);
};
#endif // AST_H
