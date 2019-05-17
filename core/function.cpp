#include "function.h"
#include <algorithm>
#include <iostream>
#include "core.h"
#include "builtin/builtin.h"
#include "builtin/_string.h"
#include "builtin/int.h"
#include "builtin/char.h"
#include "builtin/void.h"
#include "builtin/bool.h"
root_function::root_function(const root* parent) : root("function", parent)
{
}
function::function(const root* parent) : root("function", parent)
{
}
root* function::new_this()
{
	dm.insert("builtin", new variable((new builtin)->new_this()));
	return this;
}

void function::run()
{
	for (const auto& x : commands)
	{
		DEB(TS_ID_16 + x);
		delete convert_var(x);
	}
}
root* function::make_copy()
{
	auto x = new function(this->parent);
	x->commands = this->commands;
	return x;
}
variable* function::member_access(const std::string & name)
{
	if (name.find('.') != std::string::npos)
	{
		auto s = domain::SplitString(name, ".");
		if (s.size() < 2)
		{
			ERR(TS_ID_32);
			return nullptr;
		}
		variable* p = dm.get(s[0]);
		for (size_t i = 1; i < s.size() && p != nullptr; i++)
		{
			if (p != nullptr && p->get() != nullptr)
				p = p->get()->access_member(s[i]);
			else
				ERR(TS_ID_31 + name);
		}
		if (p == nullptr || p->get() == nullptr) {
			ERR(TS_ID_31 + name);
			return nullptr;
		}
		return p->copy();
	}
	else
	{
		return dm[name]->copy();
	}
}
std::pair<std::string, std::vector<std::string>> function::ProcessCmd(std::string str) const
{
	std::pair<std::string, std::vector<std::string>> buf;
	if (str.find('(') == std::string::npos)
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
	buf.first = domain::SplitString(str, "(")[0];
	str = str.substr(str.find_first_of('(') + 1);
	str = str.erase(str.find_last_of(')'));
	std::vector<std::string> args = domain::SplitString(str, ","), buf_;
	for (const auto& arg : args)
	{
		if (buf_.empty())
		{
			buf_.push_back(arg);
			continue;
		}
		auto x = buf_[(buf_.size() - 1)];
		if (std::count(x.begin(), x.end(), '(') != std::count(x.begin(), x.end(), ')'))
		{
			x.append("," + arg);
			buf_.erase(buf_.end() - 1);
			buf_.push_back(x);
		}
		else
		{
			buf_.push_back(arg);
		}
	}
	buf.second = buf_;
	return buf;
}
variable* function::convert_var(const std::string & token)
{
	auto x = ProcessCmd(token);
	if (token.find('(') == std::basic_string<char, std::char_traits<char>, std::allocator<char>>::npos)
	{
		return member_access(x.first);
	}
	else
	{
		SWITCH_BEGIN(x.first)
			SWITCH_CASE("string")
		{
			std::string str;
			for (const auto& i : x.second)
				str += ((!str.empty()) ? "," : "") + i;
			return new variable((new root_string(str))->new_this());
		}
		SWITCH_CASE("int")
		{
			std::string str;
			for (const auto& i : x.second)
				str += ((!str.empty()) ? "," : "") + i;
			return new variable((new root_int(std::stoi(str)))->new_this());
		}
		SWITCH_CASE("char")
		{
			std::string str;
			for (const auto& i : x.second)
				str += ((!str.empty()) ? "," : "") + i;
			return new variable((new root_char(static_cast<char>(std::stoi(str))))->new_this());
		}
		SWITCH_CASE("void")
		{
			return new variable((new root_void())->new_this());
		}
		SWITCH_CASE("bool")
		{
			std::string str;
			for (const auto& i : x.second)
				str += ((!str.empty()) ? "," : "") + i;
			return new variable((new root_bool(str == "true"))->new_this());
		}
		SWITCH_DEFAULT{
			std::vector<variable*> c;
			for (size_t i = 0; i < x.second.size(); ++i)
				c.push_back(convert_var(x.second[i]));
			DEB(TS_ID_30 + x.first);
			auto t = member_access(x.first);
			if (t != nullptr)
			{
				if (t->get() != nullptr) {
					const auto n = t;
					t = t->get()->execute(c);
					delete n;
					if (t == nullptr) {
						ERR(TS_ID_33 + x.first);
					}
				}
 else {
  ERR(TS_ID_31 + x.first);
  delete t;
  t = nullptr;
}
}
else
{
	ERR(TS_ID_31 + x.first);
}
for (const auto& m : c)
	delete m;
return t;
		}
			SWITCH_END
	}
}
void function::ProcessDefine(const std::string & str)
{
	if (str.empty())
	{
		ERR(TS_ID_1);
		return;
	}
	std::vector<std::string> v = domain::SplitString(str, "\n");
	for (auto m : v)
	{
		if (m.find('#') != std::string::npos) {
			m = domain::SplitString(m, "#")[0];
		}
		if (m.length() == 0)
		{
			continue;
		}
		commands.push_back(m);
		DEB("cmd " + m);
	}
}