#ifndef CMDER_H
#define CMDER_H
#include "log.h"
#include "ServerCore.h"
#include "cmder_conf.h"
#include <functional>
#include <cstdlib>
#include <utility>
#include <map>
#include "database.h"

#define CMD_PAIR(key,value) std::make_pair(key,std::function<data_container*(std::vector<data_container*>)>(value))
class cmder :public cmder_conf {
	friend cmder_conf;
public:
	cmder();
	// Run Functions in ConfigMgr
	void run();
	typedef std::pair<std::string, std::vector<data_container*>> cmd;
private:
	std::pair<std::string, std::vector<std::string>> ProcessCmd(std::string str) const;
	std::pair<bool, data_container*> convert_var(std::string token);
};
class executable
{
public:
	executable(cmder_conf&);
	static void insert_static_function(const std::string& key, const std::function<data_container* (std::vector<data_container*>)>& value);
	static std::function<data_container* (std::vector<data_container*>)> call(const std::string& key);
	static std::map<std::string, std::function<data_container* (std::vector<data_container*>)>> static_functions;
	data_container* execute(cmder::cmd command) const;

	static data_container* echo(std::vector<data_container*>);
	static data_container* var(std::vector<data_container*>);
protected:
private:
	cmder_conf& mgr;
};

#endif
