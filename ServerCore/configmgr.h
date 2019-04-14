#ifndef CONFIG_MGR_H
#define CONFIG_MGR_H
#include "file.h"
#include "ServerCore.h"
#include "database.h"

class ConfigMgr : public _database {
public:
	ConfigMgr(const bool& open_file, const std::string& config_name);
	std::vector<std::string> commands;
protected:
	std::string create_database_string() override;
	//void str_insert(std::string& str, const std::string& key, _data*) override;
	void cmd_insert(std::string& str, const std::string& command);
	std::string map_to_str() override;
	void str_to_map(const std::string& str) override;
};

#endif // CONFIG_MGR_H
