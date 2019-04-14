#include "cmder.h"

cmder::cmder(const bool& open_file, const std::string& config_name) : ConfigMgr(open_file, config_name)
{
}

void cmder::run()
{
	DEB(TS_ID_16);
	for (size_t i = 0; i < commands.size(); ++i)
	{
		delete convert_var(commands[i]);
	}
}
std::pair<std::string, std::vector<std::string>> cmder::ProcessCmd(std::string str)
{
	std::pair<std::string, std::vector<std::string>> buf;
	if (str.find("(") == std::string::npos)
	{
		ERR(TS_ID_15 "(");
		return buf;
	}
	if (std::count(str.begin(), str.end(), (int)'(') == std::count(str.begin(), str.end(), (int)')'))
	{
		ERR(TS_ID_15);
		return buf;
	}
	buf.first = _database::SplitString(str, "(")[0];
	str = str.substr(str.find_first_of("("));
	str = str.erase(str.find_last_of(")"));
	std::vector<std::string> args = _database::SplitString(str, ","), buf_;
	for (size_t t = 0; t < args.size(); ++t) {
		auto x = buf_[(buf_.size() == 0) ? 0 : (buf_.size() - 1)];
		if (!(std::count(x.begin(), x.end(), (int)'(') == std::count(x.begin(), x.end(), (int)')')))
		{
			x.append(args[t]);
			buf_.erase(buf_.end());
			buf_.push_back(x);
		}
		else
		{
			buf_.push_back(args[t]);
		}
	}
	buf.second = buf_;
	return buf;
}
_data* cmder::convert_var(std::string token)
{
	//var(string x,string(ha))
	auto x = ProcessCmd(token);
	if (x.first.find(" ") != x.first.npos)
	{
		if (_database::SplitString(x.first, " ").size() > 1)
		{
			auto ptr = new _data(_database::SplitString(x.first, " ")[1]);
			insert(_database::SplitString(x.first, " ")[0], ptr);
			return ptr;
		}
		else
		{
			return (*this)[x.first];
		}
	}
	else
	{
		std::vector<_data*> v;
		for (size_t i; i < x.second.size(); ++i)
		{
			v.push_back(convert_var(x.second[i]));
		}
		cmd c;
		c.first = x.first;
		c.second = v;
		return executable(*this).execute(c);
	}
}

executable::executable(ConfigMgr& m) :mgr(m)
{
}

void executable::insert_static_function(const std::string& key, const std::function<_data* (std::vector<_data*>)>& value)
{
	DEB(TS_ID_7 " " + key);
	static_functions.insert(std::make_pair(key, value));
}

std::function<_data* (std::vector<_data*>)> executable::call(const std::string & key)
{
	DEB(TS_ID_8 " " + key);
	return static_functions[key];
}

//void executable::echo(std::vector<_data*> args)
//{
//	for_each(args.begin(), args.end(), [&](_data * d) {
//		switch (d->what())
//		{
//		case _data::Int:
//			std::cout << d->getInt().second;
//			break;
//		case _data::Bool:
//			std::cout << ((d->getBool().second) ? "true" : "false");
//			break;
//		case _data::String:
//			std::cout << d->getString().second;
//			break;
//		case _data::Void:
//			std::cout << "void";
//			break;
//		}
//		});
//}

std::map<std::string, std::function<_data* (std::vector<_data*>)>> executable::static_functions({
	//CMD_PAIR("echo",&executable::echo),
	//CMD_PAIR("endl",&executable::endl),
	//CMD_PAIR("system",&executable::_system),
	//CMD_PAIR("cast",&executable::cast),
	//CMD_PAIR("log",&executable::log_verbose),
	//CMD_PAIR("cin",&executable::cin),
	//CMD_PAIR("var",&executable::var)
	});

_data * executable::execute(cmder::cmd command)
{
	if (static_functions.find(command.first) == static_functions.end())
	{
		ERR(TS_ID_17 " \"" + command.first + "\"");
		return nullptr;
	}
	return static_functions[command.first](command.second);
}
//void executable::endl(std::vector<_data*>)
//{
//	std::cout << std::endl;
//}
//void executable::_system(std::vector<_data*> args)
//{
//	for_each(args.begin(), args.end(), [&](_data * d) {
//		switch (d->what())
//		{
//		case _data::Int:
//			ERR(TS_ID_19 TS_ID_21);
//			break;
//		case _data::Bool:
//			ERR(TS_ID_19 TS_ID_22);
//			break;
//		case _data::String:
//			system(d->getString().second.c_str());
//			break;
//		case _data::Void:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		}
//		});
//}
//
//void executable::cast(std::vector<_data*> args)
//{
//	if (args.size() != 2)
//	{
//		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
//	}
//	switch (args[0]->what())
//	{
//	case _data::String:
//		switch (args[1]->what())
//		{
//		case _data::String:
//			args[1]->setValue(args[0]->getString().second);
//			break;
//		case _data::Int:
//			args[1]->setValue(stoi(args[0]->getString().second));
//			break;
//		case _data::Bool:
//			args[1]->setValue(args[0]->getString().second == "true" ? true : false);
//			break;
//		default:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		};
//		break;
//	case _data::Bool:
//		switch (args[1]->what())
//		{
//		case _data::String:
//			args[1]->setValue(args[0]->getBool().second ? "true" : "false");
//			break;
//		case _data::Int:
//			args[1]->setValue((int)(args[0]->getBool().second));
//			break;
//		case _data::Bool:
//			args[1]->setValue(args[0]->getBool().second);
//			break;
//		default:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		};
//		break;
//	case _data::Int:
//		switch (args[1]->what())
//		{
//		case _data::String:
//			args[1]->setValue(std::to_string(args[0]->getInt().second));
//			break;
//		case _data::Int:
//			args[1]->setValue(args[0]->getInt().second);
//			break;
//		case _data::Bool:
//			args[1]->setValue(args[0]->getInt().second == 0 ? false : true);
//			break;
//		default:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		};
//		break;
//	default:
//		ERR(TS_ID_19 TS_ID_23);
//		break;
//	}
//}
//
//void executable::log_verbose(std::vector<_data*> args)
//{
//	if (args.size() != 1)
//	{
//		ERR(TS_ID_24 "1" TS_ID_25 TS_ID_26);
//		return;
//	}
//	if (if_type_is(args[0], Int)) {
//		log::verbose = (log::log_level)args[0]->getInt().second;
//	}
//	else
//	{
//		ERR(TS_ID_19);
//	}
//}
//
//void executable::cin(std::vector<_data*> args)
//{
//	for_each(args.begin(), args.end(), [&](_data * d) {
//		switch (d->what())
//		{
//		case _data::String:
//		{
//			std::string str;
//			std::cin >> str;
//			d->setValue(str);
//			break;
//		}
//		default:
//			ERR(TS_ID_19);
//			break;
//		}
//		});
//}
//
//void executable::var(std::vector<_data*> args)
//{
//	if (args.size() == 2)
//	{
//		switch (args[1]->what())
//		{
//		case _data::String:
//			args[0]->setValue(args[1]->getString().second);
//			break;
//		case _data::Int:
//			args[0]->setValue(args[1]->getInt().second);
//			break;
//		case _data::Bool:
//			args[0]->setValue(args[1]->getBool().second);
//			break;
//		case _data::Void:
//			args[0]->clearValue();
//			break;
//		};
//	}
//	else
//	{
//		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
//	}
//}