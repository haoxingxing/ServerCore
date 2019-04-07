#include "configmgr.h"
#include "cmder.h"
ConfigMgr::ConfigMgr(const std::string & config_name) :_database(true, config_name + ".conf")
{
}

std::string ConfigMgr::create_database_string()
{
	return std::string(
		CONF_FILE_NOTICE_MSG
	);
}


void ConfigMgr::str_insert(std::string & str, const std::string & key, _data * d)
{
	str += "var ";
	str += key;
	str += "=";
	switch (d->what()) {
	case _data::Int:
		str += "int";
		str += "=";
		str += std::to_string(d->getInt().second);
		break;
	case _data::Bool:
		str += "bool";
		str += "=";
		str += std::to_string(d->getBool().second);
		break;
	case _data::String:
		str += "string";
		str += "=";
		str += d->getString().second;
		break;
	case _data::Void:
		str += "void";
		str += "=";
		break;
	};
	str += "\n";
}

void ConfigMgr::cmd_insert(std::string & str, const std::string & command)
{
	str += command;
	str += "\n";
}

std::string ConfigMgr::map_to_str()
{
	std::string buf = create_database_string();
	std::for_each(data.begin(), data.end(), [&](std::pair<std::string, _data*> d) {
		str_insert(buf, d.first, d.second);
	});
	for (size_t i = 0; i < commands.size(); ++i)
	{
		cmd_insert(buf, commands[i]);
	}
	return buf;
}

void ConfigMgr::str_to_map(const std::string & str)
{
	if (str.size() == 0)
	{
		ERR(TS_ID_1);
		return;
	}
	std::vector<std::string> v = SplitString(str, "\n");
	for (size_t i = 0; i < v.size(); ++i)
	{
		std::string m = v[i];
		if (m.find("#") != std::string::npos) {
			m = SplitString(m, "#")[0];
		}
		if (m.length() == 0)
		{
			continue;
		}
		commands.push_back(m);
		DEB("cmd " + m);
	}
}
