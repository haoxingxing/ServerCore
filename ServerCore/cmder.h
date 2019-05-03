#ifndef CMDER_H
#define CMDER_H
#include "cmder_conf.h"
#include <functional>
#include <utility>
#include "database.h"
#define CMD_PAIR(key,value) std::make_pair(key,std::function<data_container*(std::vector<data_container*>)>(value))
class cmder :public cmder_conf {
	friend cmder_conf;
public:
	cmder();
	// Run Functions in ConfigMgr
	void run();
	data_container* member_access(const std::string& name);
	typedef std::pair<std::string, std::vector<data_container*>> cmd;
private:
	std::pair<std::string, std::vector<std::string>> ProcessCmd(std::string str) const;
	data_container* convert_var(std::string token);
};
#endif
