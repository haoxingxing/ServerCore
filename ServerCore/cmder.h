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

#define CMD_PAIR(key,value) std::make_pair(key,std::function<data*(std::vector<data*>)>(value))
class cmder :public cmder_conf {
	friend cmder_conf;
public:
	cmder();
	// Run Functions in ConfigMgr
	void run();
	typedef std::pair<std::string, std::vector<data*>> cmd;
private:
	std::pair<std::string, std::vector<std::string>> ProcessCmd(std::string str) const;
	data* convert_var(std::string token);
};
class executable
{
public:
	executable(cmder_conf&);
	static void insert_static_function(const std::string& key, const std::function<data* (std::vector<data*>)>& value);
	static std::function<data* (std::vector<data*>)> call(const std::string& key);
	static std::map<std::string, std::function<data* (std::vector<data*>)>> static_functions;
	data* execute(cmder::cmd command) const;

	static data* echo(std::vector<data*>);
	static data* var(std::vector<data*>);
protected:
private:
	cmder_conf& mgr;
};

#endif
