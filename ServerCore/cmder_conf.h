#ifndef CONFIG_MGR_H
#define CONFIG_MGR_H
#include "ServerCore.h"
#include "database.h"

class cmder_conf : public database {
public:
	cmder_conf();
	std::vector<std::string> commands;
protected:	
	void str_to_map(const std::string& str);
};

#endif // CONFIG_MGR_H
