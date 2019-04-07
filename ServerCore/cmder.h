#ifndef CMDER_H
#define CMDER_H
#include "log.h"
#include "ServerCore.h"
#include "configmgr.h"
#include <functional>
#include <cstdlib>

#define CMD_PAIR(key,value) std::make_pair(key,std::function<void(std::vector<_data*>)>(value))
class cmder {
	friend ConfigMgr;
public:
	cmder(ConfigMgr&);
	// Run Functions in ConfigMgr
	void run();	
	typedef std::pair<std::string, std::vector<_data*>> cmd;
private:
	ConfigMgr& mgr;
	cmd ResolveCommand(std::string str);
	_data* convert_var(std::string token);
	std::vector <std::vector<_data* >> Recover;
	size_t what_now = 0;
};
class executable
{
public:
	executable(ConfigMgr&);
	static void insert_static_function(const std::string& key,const std::function<void(std::vector<_data*>)>& value);
	static std::function<void(std::vector<_data*>)> call(const std::string&key);
	static std::map<std::string, std::function<void(std::vector<_data*>)>> static_functions;
	void execute(cmder::cmd command);
	/*
	 * Built-in Function:
	 */
	static void endl(std::vector<_data*>);
	static void echo(std::vector<_data*>);
	static void _system(std::vector<_data*>);
	static void cast(std::vector<_data*>);
	static void log_verbose(std::vector<_data*>);
	static void cin(std::vector<_data*>);
	static void var(std::vector<_data*>);
protected:
private:
	ConfigMgr& mgr;
};

#endif
