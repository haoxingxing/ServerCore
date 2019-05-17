#ifndef FUNCTION_H
#define FUNCTION_H
#include <utility>
#include "domain.h"
#define CMD_PAIR(key,value) std::make_pair(key,std::function<variable*(std::vector<variable*>)>(value))
class function :public root {
public:
	function(const root* parent = nullptr);
	root* new_this() override;
	void run();
	root* make_copy() override;
	variable* member_access(const std::string& name);
	void ProcessDefine(const std::string&);
private:
	std::pair<std::string, std::vector<std::string>> ProcessCmd(std::string str) const;
	variable* convert_var(const std::string& token);
	std::vector<std::string> commands;
	domain dm;
};
#endif
