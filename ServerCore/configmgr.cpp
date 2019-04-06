#include "configmgr.h"

ConfigMgr::ConfigMgr(const std::string & config_name) :_database(true, config_name + ".conf")
{
}

std::string ConfigMgr::create_database_string()
{
	return std::string(
		"# Config File\n"
	);
}

void ConfigMgr::str_insert(std::string & str, const std::string & key, _data * d)
{
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

std::string ConfigMgr::map_to_str(const std::map<std::string, _data*>& m)
{
	std::string buf = create_database_string();
	std::for_each(m.begin(), m.end(), [&](std::pair<std::string, _data*> d) {
		str_insert(buf, d.first, d.second);
	});
	return buf;
}

std::map<std::string, _data*> ConfigMgr::str_to_map(const std::string & str)
{
	std::map<std::string, _data*> buf;
	if (str.size() == 0)
	{
		ERR("Invalid Database String");
		return buf;
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
		if (m.find('=') == std::string::npos)
		{
			WARN("Invalid Group: '=' Not Find");
			continue;
		}
		std::vector<std::string> b = SplitString(m, "=");
		if (b.size() != 3)
		{
			WARN("Invalid Group: Check is there so many '=' sign");
			continue;
		}
		switch (b[1].at(0))
		{
		case 'i':
			buf.insert(std::make_pair(b[0], new _data(std::stoi(b[2]))));
			break;
		case 'b':
			buf.insert(std::make_pair(b[0], new _data(std::stoi(b[2]) != 0)));
			break;
		case 's':
			buf.insert(std::make_pair(b[0], new _data(b[2])));
			break;
		case 'v':
			buf.insert(std::make_pair(b[0], new _data()));
			break;
		default:
			WARN("Invalid Type");
			break;
		}
	}
	return buf;
}
