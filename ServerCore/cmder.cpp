#include "cmder.h"
#include <algorithm>
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
		//DEB(TS_ID_15 "(");
		buf.first.append(str);
		return buf;
	}
	if (std::count(str.begin(), str.end(), '(') != std::count(str.begin(), str.end(), ')'))
	{
		ERR(TS_ID_15);
		return buf;
	}
	buf.first = database::SplitString(str, "(")[0];
	str = str.substr(str.find_first_of('(')+1);
	str = str.erase(str.find_last_of(')'));
	std::vector<std::string> args = database::SplitString(str, ","), buf_;
	for (size_t t = 0; t < args.size(); ++t) {
		if (buf_.size()==0)
		{
			buf_.push_back(args[t]);
			continue;
		}
		auto x = buf_[(buf_.size() - 1)];
		if (!(std::count(x.begin(), x.end(), '(') == std::count(x.begin(), x.end(), ')')))
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
	auto x = ProcessCmd(token);
	if (x.first.find(" ") != std::basic_string<char, std::char_traits<char>, std::allocator<char>>::npos)
	{
		if (database::SplitString(x.first, " ").size() > 1)
		{
			auto ptr = new data_container(database::SplitString(x.first, " ")[0]);
			insert(database::SplitString(x.first, " ")[1], ptr);
			return ptr;
		}
		else
		{		
			return (*this)[x.first]->copy();
		}
	}
	else
	{
		_SWITCH_BEGIN(x.first)
			_SWITCH_CASE("string")
			{
				std::string str;
				for (size_t i =0;i<x.second.size();++i)
				{
					str += ((str.size()!=0)?",":"") + x.second[i];
				}
				return new data_container("string",new data_string(str));
			}
			_SWITCH_DEFAULT {
				cmd c;
				for (size_t i = 0; i < x.second.size(); ++i)
				{
					c.second.push_back(convert_var(x.second[i]));
				}
				c.first = x.first;
				auto t= executable(*this).execute(c);
				//for (size_t i = 0; i < c.second.size(); ++i)
				//{
				//	delete c.second[i];
				//}
				return t;
			}
		_SWITCH_END
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

std::map<std::string, std::function<data_container*(std::vector<data_container*>)>> executable::static_functions({
	CMD_PAIR("var",&executable::var)
	 
});

data_container* executable::execute(cmder::cmd command) const
{
	if (static_functions.find(command.first) == static_functions.end())
	{
		ERR(TS_ID_17 " \"" + command.first + "\"");
		return nullptr;
	}
	return static_functions[command.first](command.second);
}

data_container* executable::echo(std::vector<data_container*> n)
{

	return nullptr;
}

data_container* executable::var(std::vector<data_container*> args)
{
	args[0]->swap(args[1]);
	return nullptr;
}
