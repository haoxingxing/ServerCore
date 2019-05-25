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

void function::run(const ast::tree& t)
{
	delete this->Process(t);
}
root* function::make_copy()
{
	auto x = new function(this->parent);
	x->Tree = this->Tree;
	return x;
}
variable* function::member_access(const std::string& name)
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
	if (name.empty())
		return  new variable((new root_void())->new_this());
	if (std::find_if(name.begin(), name.end(), [](char c) { return !std::isdigit(c); }) == name.end())
		return new variable((new root_int(std::stoi(name)))->new_this());
	if (name.find('"') != std::string::npos)
		return new variable((new root_string(name.substr(1).substr(0, name.size() - 2)))->new_this());
	if (name == "true" || name == "false")
		return  new variable((new root_bool(name == "true"))->new_this());
	if (name.find('\'') != std::string::npos)
		return new variable((new root_char(name.length() < 3 ? char(0) : (name.substr(1).substr(0, name.size() - 2).at(0))))->new_this());
	return dm[name]->copy();
}
variable * function::Process(const ast::tree & T)
{
	if (T.args.empty())
	{
		return member_access(T.data);
	}
	SWITCH_BEGIN(T.data)
		SWITCH_CASE("function")
	{
		variable* last = nullptr;
		for (const auto& arg : T.args)
		{
			if (arg.data != "return")
			{
				delete last;
				last = Process(arg);
			}
			else
			{
				return Process(arg);
			};
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
	{
		variable* n = Process(T.args[0]);
		while (n != nullptr) {
			n = Process(T.args[0]);
			if (GET_TYPE("bool", root_bool, n->get())->access())
			{
				delete n;
				const auto x = Process(T.args[1]);
				if (x != nullptr) {
					return x;
				}
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