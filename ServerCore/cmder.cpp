#include "cmder.h"

cmder::cmder()
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
std::pair<std::string, std::vector<std::string>> cmder::ProcessCmd(std::string str) const
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
	buf.first = database::SplitString(str, "(")[0];
	str = str.substr(str.find_first_of("("));
	str = str.erase(str.find_last_of(")"));
	std::vector<std::string> args = database::SplitString(str, ","), buf_;
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
data_container* cmder::convert_var(std::string token)
{
	//var(string x,string(ha))
	auto x = ProcessCmd(token);
	if (x.first.find(" ") != x.first.npos)
	{
		if (database::SplitString(x.first, " ").size() > 1)
		{
			auto ptr = new data_container(database::SplitString(x.first, " ")[1]);
			insert(database::SplitString(x.first, " ")[0], ptr);
			return ptr;
		}
		else
		{
			return (*this)[x.first];
		}
	}
	else
	{
		std::vector<data_container*> v;
		for (size_t i = 0; i < x.second.size(); ++i)
		{
			v.push_back(convert_var(x.second[i]));
		}
		cmd c;
		c.first = x.first;
		c.second = v;
		return executable(*this).execute(c);
	}
}

executable::executable(cmder_conf& m) :mgr(m)
{
}

void executable::insert_static_function(const std::string& key, const std::function<data_container* (std::vector<data_container*>)>& value)
{
	DEB(TS_ID_7 " " + key);
	static_functions.insert(std::make_pair(key, value));
}

std::function<data_container* (std::vector<data_container*>)> executable::call(const std::string & key)
{
	DEB(TS_ID_8 " " + key);
	return static_functions[key];
}

//void executable::echo(std::vector<data_container*> args)
//{
//	for_each(args.begin(), args.end(), [&](data_container * d) {
//		switch (d->what())
//		{
//		case data_container::Int:
//			std::cout << d->getInt().second;
//			break;
//		case data_container::Bool:
//			std::cout << ((d->getBool().second) ? "true" : "false");
//			break;
//		case data_container::String:
//			std::cout << d->getString().second;
//			break;
//		case data_container::Void:
//			std::cout << "void";
//			break;
//		}
//		});
//}

std::map<std::string, std::function<data_container* (std::vector<data_container*>)>> executable::static_functions({
	//CMD_PAIR("echo",&executable::echo),
	//CMD_PAIR("endl",&executable::endl),
	//CMD_PAIR("system",&executable::_system),
	//CMD_PAIR("cast",&executable::cast),
	//CMD_PAIR("log",&executable::log_verbose),
	//CMD_PAIR("cin",&executable::cin),
	//CMD_PAIR("var",&executable::var)
	});

data_container * executable::execute(cmder::cmd command) const
{
	if (static_functions.find(command.first) == static_functions.end())
	{
		ERR(TS_ID_17 " \"" + command.first + "\"");
		return nullptr;
	}
	return static_functions[command.first](command.second);
}
//void executable::endl(std::vector<data_container*>)
//{
//	std::cout << std::endl;
//}
//void executable::_system(std::vector<data_container*> args)
//{
//	for_each(args.begin(), args.end(), [&](data_container * d) {
//		switch (d->what())
//		{
//		case data_container::Int:
//			ERR(TS_ID_19 TS_ID_21);
//			break;
//		case data_container::Bool:
//			ERR(TS_ID_19 TS_ID_22);
//			break;
//		case data_container::String:
//			system(d->getString().second.c_str());
//			break;
//		case data_container::Void:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		}
//		});
//}
//
//void executable::cast(std::vector<data_container*> args)
//{
//	if (args.size() != 2)
//	{
//		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
//	}
//	switch (args[0]->what())
//	{
//	case data_container::String:
//		switch (args[1]->what())
//		{
//		case data_container::String:
//			args[1]->setValue(args[0]->getString().second);
//			break;
//		case data_container::Int:
//			args[1]->setValue(stoi(args[0]->getString().second));
//			break;
//		case data_container::Bool:
//			args[1]->setValue(args[0]->getString().second == "true" ? true : false);
//			break;
//		default:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		};
//		break;
//	case data_container::Bool:
//		switch (args[1]->what())
//		{
//		case data_container::String:
//			args[1]->setValue(args[0]->getBool().second ? "true" : "false");
//			break;
//		case data_container::Int:
//			args[1]->setValue((int)(args[0]->getBool().second));
//			break;
//		case data_container::Bool:
//			args[1]->setValue(args[0]->getBool().second);
//			break;
//		default:
//			ERR(TS_ID_19 TS_ID_23);
//			break;
//		};
//		break;
//	case data_container::Int:
//		switch (args[1]->what())
//		{
//		case data_container::String:
//			args[1]->setValue(std::to_string(args[0]->getInt().second));
//			break;
//		case data_container::Int:
//			args[1]->setValue(args[0]->getInt().second);
//			break;
//		case data_container::Bool:
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
//void executable::log_verbose(std::vector<data_container*> args)
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
//void executable::cin(std::vector<data_container*> args)
//{
//	for_each(args.begin(), args.end(), [&](data_container * d) {
//		switch (d->what())
//		{
//		case data_container::String:
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
//void executable::var(std::vector<data_container*> args)
//{
//	if (args.size() == 2)
//	{
//		switch (args[1]->what())
//		{
//		case data_container::String:
//			args[0]->setValue(args[1]->getString().second);
//			break;
//		case data_container::Int:
//			args[0]->setValue(args[1]->getInt().second);
//			break;
//		case data_container::Bool:
//			args[0]->setValue(args[1]->getBool().second);
//			break;
//		case data_container::Void:
//			args[0]->clearValue();
//			break;
//		};
//	}
//	else
//	{
//		ERR(TS_ID_24 "2" TS_ID_25 TS_ID_26);
//	}
//}