#ifndef CMDER_H
#define CMDER_H
#include "log.h"
#include "ServerCore.h"
#include "configmgr.h"
class cmder {
public:
	cmder(ConfigMgr&);
	void run();
	typedef std::pair<std::string, std::vector<_data*>> cmd;
private:
	ConfigMgr& mgr;
	cmd ResolveCommand(std::string str);
	_data* convert_var(std::string token);
};

#endif
