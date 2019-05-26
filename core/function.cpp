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
#include  <cctype>
root_function::root_function(root* parent) : root("_function", parent)
{
}
_function::_function(root* parent) : root("_function", parent)
{
}
root* _function::new_this()
{
	member->insert("builtin", new variable((new builtin(this))->new_this()));
	return this;
}

void _function::run(const ast::tree& t)
{
	delete this->Process(t);
}
root* _function::make_copy()
{
	auto x = new _function(this->parent);
	x->Tree = this->Tree;
	return x;
}
variable* _function::member_access(const std::string& name)
{
	if (name.find('.') != std::string::npos)
	{
		auto s = domain::SplitString(name, ".");
		if (s.size() < 2)
		{
			ERR(TS_ID_32);
			return nullptr;
		}//TODO: 		variable* p = member_access(s[0]);
		variable* p = member->get(s[0]);
		for (size_t i = 1; i < s.size() && p != nullptr; i++)
		{
			if (p != nullptr && p->get() != nullptr) {
				p = p->get()->access_member(s[i]);
			}
			else
				ERR(TS_ID_31 + name);
		}

		if (p == nullptr || p->get() == nullptr) {
			ERR(TS_ID_31 + name);
			return nullptr;
		}
		return p->copy();
	}
	if (name.empty())
		return new variable((new root_void())->new_this());
	if (std::find_if(name.begin(), name.end(), [](char c) { return !std::isdigit(c); }) == name.end())
		return new variable((new root_int(std::stoi(name)))->new_this());
	if (name.find('"') != std::string::npos) {
		auto x = name.substr(1).substr(0, name.size() - 2);
		x = ReplaceAll(x, "\\n", "\n");
		return new variable((new root_string(x))->new_this());
	}
	if (name == "true" || name == "false")
		return  new variable((new root_bool(name == "true"))->new_this());
	if (name.find('\'') != std::string::npos)
		return new variable((new root_char(name.length() < 3 ? char(0) : (name.substr(1).substr(0, name.size() - 2).at(0))))->new_this());
	return (*member)[name]->copy();
}
std::string _function::ReplaceAll(std::string str, const std::string & from, const std::string & to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
variable* _function::Process(const ast::tree & T)
{
	if (T.args.empty())
	{
		return member_access(T.data);
	}
	SWITCH_BEGIN(T.data)
		SWITCH_CASE("function")
	{
		//variable* last = nullptr;
		for (const auto& arg : T.args)
		{
			if (arg.data != "return")
			{
				delete Process(arg);
			}
			else
			{
				return Process(arg);
			};
		}
		return nullptr;
	}
	SWITCH_CASE("args_list")
	{
		variable* last = nullptr;
		for (const auto& arg : T.args)
		{
			delete last;
			last = Process(arg);
		}
		return last;
	}
	SWITCH_CASE("if")
	{
		const auto x = Process(T.args[0]);
		if (x != nullptr)
			if (GET_TYPE("bool", root_bool, x->get())->access()) {
				delete x;
				return Process(T.args[1]);
			}
		delete x;
		return Process(T.args[2]);
	}
	SWITCH_CASE("while")
	{//TODO:在循环中的return
		variable* n = Process(T.args[0]);
		while (n != nullptr) {
			delete n;
			n = Process(T.args[0]);
			if (GET_TYPE("bool", root_bool, n->get())->access())
			{
				const auto x = Process(T.args[1]);
				if (x != nullptr)
				{
					return x;
				}
			}
			else {
				delete n;
				break;
			}
		}
		return nullptr;
	}
	SWITCH_DEFAULT
	{
		std::vector<variable*> c;
		for (const auto& arg : T.args[0].args)
			c.push_back(Process(arg));
		DEB(TS_ID_30 + T.data);
		auto t = member_access(T.data);
		if (t != nullptr)
		{
			if (t->get() != nullptr) {
				const auto n = t;
				t = t->get()->execute(c);
				delete n;
				if (t == nullptr) {
					ERR(TS_ID_33 + T.data);
				}
			}
			else {
				ERR(TS_ID_31 + T.data);
				delete t;
				t = nullptr;
			}
		}
		else
		{
			ERR(TS_ID_31 + T.data);
		}
		for (const auto& m : c)
			delete m;
		return t;
	}
		SWITCH_END
}