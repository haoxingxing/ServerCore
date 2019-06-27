#ifndef FUNCTION_H
#define FUNCTION_H
#include "domain.h"
#include "ast.h"
#define CMD_PAIR(key,value) std::make_pair(key,std::_function<variable*(std::vector<variable*>)>(value))
class _function :public root {
public:
	explicit _function(root* parent = nullptr);
	root* new_this() override;
	void run(const ast::tree&);
	root* make_copy() override;
	variable* member_access(const std::string& name) const;
private:
	static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	variable* Process(const ast::tree& T) const;
	ast::tree Tree;
};
#endif
