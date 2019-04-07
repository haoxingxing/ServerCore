#include "cmder.h"
cmder::cmder(ConfigMgr &d):mgr(d)
{
	
}
void cmder::run()
{
	for (size_t i = 0; i < mgr.commands.size(); ++i)
	{
		ResolveCommand(mgr.commands[i]);
	}
}
cmder::cmd cmder::ResolveCommand(std::string str)
{
	LOG(TS_ID_16);
	cmd buf;
	if (str.find("(") == std::string::npos)
	{
		ERR(TS_ID_15 "(");
		return buf;
	}
	if (str.find(")") == std::string::npos)
	{
		ERR(TS_ID_15 ")");
		return buf;
	}
	buf.first = _database::SplitString(str, "(")[0];
	str = _database::SplitString(_database::SplitString(str, "(")[1],")")[0];
	std::vector<std::string> args = _database::SplitString(str, ",");
	for (size_t i = 0; i < args.size(); ++i)
	{
		buf.second.push_back(convert_var(args[i]));
	}
	return buf;
}

_data* cmder::convert_var(std::string token)
{	
	if (token.find("var ") != token.npos)
	{
		return mgr[token.substr(4)];
	}
	else
	{
		switch (token.at(0))
		{
		case 'i':
			return new _data(std::stoi(token.substr(4)));
			break;
		case 'b':
			return new _data(std::stoi(token.substr(5)) != 0);
			break;
		case 's':
			return new _data(token.substr(7));
			break;
		case 'v':
		    return new _data();
			break;
		default:
			WARN(TS_ID_3);
			return new _data();
			break;
		}
	}
}
