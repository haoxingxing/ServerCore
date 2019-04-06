#ifndef CONFIG_MGR_H
#define CONFIG_MGR_H
#include "file.h"
#include "ServerCore.h"
#include "database.h"

class ConfigMgr : public _database {
public:
	ConfigMgr(const std::string& config_name);
protected:
	std::string create_database_string() override;
	void str_insert(std::string& str, const std::string& key, _data*) override;
	std::string map_to_str(const std::map<std::string, _data*> &) override;
	std::map<std::string, _data*> str_to_map(const std::string &str) override;
};

#endif // CONFIG_MGR_H
