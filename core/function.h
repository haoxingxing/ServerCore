#ifndef FUNCTION_H
#define FUNCTION_H
#include "domain.h"
#include "ast.h"
#define CMD_PAIR(key,value) std::make_pair(key,std::_function<variable*(std::vector<variable*>)>(value))
class _function :public root {
public:
	explicit _function(root* parent = nullptr);
	root* new_this() override;
	root* make_copy() override;
	static variable* process(ast::tree* T, domain* def);
private:
	ast::tree* Tree;
};
#endif
