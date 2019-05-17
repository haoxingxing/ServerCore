#ifndef FUNCTION_H
#define FUNCTION_H
#include <utility>
#include "domain.h"
#define CMD_PAIR(key,value) std::make_pair(key,std::function<variable*(std::vector<variable*>)>(value))
class function :public domain {
public:
	function();
	// Run Functions in ConfigMgr
	void run();
	variable* member_access(const std::string& name);
	void ProcessDefine(const std::string&);
private:
	std::pair<std::string, std::vector<std::string>> ProcessCmd(std::string str) const;
	variable* convert_var(const std::string& token);
	std::vector<std::string> commands;
};
#endif
