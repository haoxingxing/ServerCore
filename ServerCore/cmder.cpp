 #include "cmder.h"
cmder::cmder(ConfigMgr &d):mgr(d)
{}
void cmder::run()
{
	DEB(TS_ID_16);
	for (size_t i = 0; i < mgr.commands.size(); ++i)
	{
		DEB(mgr.commands[i]);
		Recover.push_back( std::vector<_data *>());
		executable(mgr).execute(ResolveCommand(mgr.commands[i]));
		for_each(Recover[i].begin(), Recover[i].end(), [&](_data* hd) {			
			delete hd;
		});
		SUCC( mgr.commands[i]);
	}
	Recover.clear();
	what_now = 0;
}
cmder::cmd cmder::ResolveCommand(std::string str)
{
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
	what_now++;
	return buf;
}

_data* cmder::convert_var(std::string token)
{	

		bool isuse = false;
		_data* ptr;
		auto v = _database::SplitString(token," ");
		std::string key,arg;
		key = v[0];
		arg = token.substr(token.find(key)+((token==key)?key.length():(key.length()+1)));			
		switch (hash_(key.c_str()))
		{
		case "int"_hash:
		{
			int b = 0;
			try {
				b = std::stoi(arg);
			}
			catch (...) {
				WARN(TS_ID_27);
			}
			ptr = new _data(b);
			break;
		}
		case "bool"_hash:
		{
			int b = 0;
			try {
				b = std::stoi(arg);
			}
			catch (...) {
				WARN(TS_ID_27);
			}
			ptr = new _data(b != 0);
			break;
		}
		case "string"_hash:
			ptr = new _data(arg);
			break;
		case "void"_hash:
		    ptr = new _data();
			break;
		default:
			if (!mgr.contains(key))
			{
				ptr = new _data();
				mgr.insert(key, ptr);
			}
			ptr = mgr[key];
			isuse = true;
			break;
		}		
		if (!isuse)
			Recover.at(what_now).push_back(ptr);
		return ptr;
}


executable::executable(ConfigMgr& m):mgr(m)
{

}

void executable::insert_static_function(const std::string & key, const std::function<void(std::vector<_data*>)>& value)
{
	DEB(TS_ID_7 " " + key);
	static_functions.insert(std::make_pair(key,value));
}

std::function<void(std::vector<_data*>)> executable::call(const std::string & key)
{
	DEB(TS_ID_8 " " + key);
	return static_functions[key];
}

void executable::echo(std::vector<_data*> args)
{
	for_each(args.begin(), args.end(), [&](_data* d) {
		switch (d->what())
		{
		case _data::Int:
			std::cout << d->getInt().second;
			break;
		case _data::Bool:
			std::cout << ((d->getBool().second) ? "true" : "false");
			break;
		case _data::String:
			std::cout << d->getString().second;
			break;
		case _data::Void:
			std::cout << "void";
			break;
		}
	});
	
}

std::map<std::string, std::function<void(std::vector<_data*>)>> executable::static_functions({
	CMD_PAIR("echo",&executable::echo),
	CMD_PAIR("endl",&executable::endl),
	CMD_PAIR("system",&executable::_system),
	CMD_PAIR("cast",&executable::cast),
	CMD_PAIR("log",&executable::log_verbose),
	CMD_PAIR("cin",&executable::cin),
	CMD_PAIR("var",&executable::var)
	});

void executable::execute(cmder::cmd command)
{
	if (static_functions.find(command.first) == static_functions.end())
	{
		ERR(TS_ID_17 " \"" + command.first + "\"");
		return;
	}
	static_functions[command.first](command.second);
}
void executable::endl(std::vector<_data*>)
{
	std::cout << std::endl;
}
void executable::_system(std::vector<_data*> args)
{
	for_each(args.begin(), args.end(), [&](_data* d) {
		switch (d->what())
		{
		case _data::Int:
			ERR(TS_ID_19 TS_ID_21);
			break;
		case _data::Bool:
			ERR(TS_ID_19 TS_ID_22);
			break;
		case _data::String:
			system(d->getString().second.c_str());
			break;
		case _data::Void:
			ERR(TS_ID_19 TS_ID_23);
			break;
		}
	});
}

void executable::cast(std::vector<_data*> args)
{
	if (args.size() != 2)
	{
		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
	}
	switch (args[0]->what())
	{
	case _data::String:
		switch (args[1]->what())
		{
		case _data::String:
			args[1]->setValue(args[0]->getString().second);
			break;
		case _data::Int:
			args[1]->setValue(stoi(args[0]->getString().second));
			break;
		case _data::Bool:
			args[1]->setValue(args[0]->getString().second == "true" ? true : false);
			break;
		default:
			ERR(TS_ID_19 TS_ID_23);
			break;
		};
		break;
	case _data::Bool:
		switch (args[1]->what())
		{
		case _data::String:
			args[1]->setValue(args[0]->getBool().second ? "true" : "false");
			break;
		case _data::Int:
			args[1]->setValue((int)(args[0]->getBool().second));
			break;
		case _data::Bool:
			args[1]->setValue(args[0]->getBool().second);
			break;
		default:
			ERR(TS_ID_19 TS_ID_23);
			break;
		};
		break;
	case _data::Int:
		switch (args[1]->what())
		{
		case _data::String:
			args[1]->setValue(std::to_string(args[0]->getInt().second));
			break;
		case _data::Int:
			args[1]->setValue(args[0]->getInt().second);
			break;
		case _data::Bool:
			args[1]->setValue(args[0]->getInt().second == 0 ? false : true);
			break;
		default:
			ERR(TS_ID_19 TS_ID_23);
			break;
		};
		break;
	default:
		ERR(TS_ID_19 TS_ID_23);
		break;
	}
}

void executable::log_verbose(std::vector<_data*> args)
{
	if (args.size() != 1)
	{
		ERR(TS_ID_24 "1" TS_ID_25 TS_ID_26);
		return;
	}
	if (if_type_is(args[0], Int)) {
		log::verbose = (log::log_level)args[0]->getInt().second;
	}
	else
	{
		ERR(TS_ID_19);
	}
	
}

void executable::cin(std::vector<_data*> args)
{
	for_each(args.begin(), args.end(), [&](_data* d) {
		switch (d->what())
		{
		case _data::String:
		{
			std::string str;
			std::cin >> str;
			d->setValue(str);
			break;
		}
		default:
			ERR(TS_ID_19);
			break;
		}
	});
}

void executable::var(std::vector<_data*> args)
{
	if (args.size() == 2)
	{
		switch (args[1]->what())
		{
		case _data::String:
			args[0]->setValue(args[1]->getString().second);
			break;
		case _data::Int:
			args[0]->setValue(args[1]->getInt().second);
			break;
		case _data::Bool:
			args[0]->setValue(args[1]->getBool().second);
			break;
		case _data::Void:
			args[0]->clearValue();
			break;
		};
	}
	else
	{
		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
	}
}
