#include "function.h"
#include <algorithm>
#include <iostream>
#include "core.h"
#include "builtin/_string.h"
#include "builtin/int.h"
#include "builtin/char.h"
#include "builtin/void.h"
#include "builtin/bool.h"
#include "builtin/s_iostream.h"
#include  <cctype>
#include "tools.h"
root_function::root_function(root* parent) : root("_function", parent)
{
}
_function::_function(root* parent) : root("_function", parent)
{
	Tree = nullptr;
}
root* _function::new_this()
{
	member->insert("iostream", new variable((new s_iostream(this))->new_this()));
	return this;
}

root* _function::make_copy()
{
	auto x = new _function(this->parent);
	x->Tree = this->Tree;
	return x;
}
variable* _function::process(ast::tree* T, domain* def)
{
	switch (T->operation)
	{
	case ast::tree::EMPTY:
	{
		if (T->key.empty())
			return new variable((new root_void())->new_this());
		if (std::find_if(T->key.begin(), T->key.end(), [](char c) { return !std::isdigit(c); }) == T->key.end())
			return new variable((new root_int(std::stoi(T->key)))->new_this());
		if (T->key.find('"') != std::string::npos) {
			auto x = T->key.substr(1).substr(0, T->key.size() - 2);
			x = stropr::ReplaceAll(x, "\\n", "\n");
			x = stropr::ReplaceAll(x, "\\r", "\r");
			return new variable((new root_string(x))->new_this());
		}
		if (T->key == "true" || T->key == "false")
			return  new variable((new root_bool(T->key == "true"))->new_this());
		if (T->key.find('\'') != std::string::npos)
			return new variable((new root_char(T->key.length() < 3 ? char(0) : (T->key.substr(1).substr(0, T->key.size() - 2).at(0))))->new_this());
		return def->get(T->key)->copy();
	}
	case ast::tree::DOT:
	{
		auto hd = process(T->left, def);
		const auto ret = hd->get()->access_member(T->right->key)->copy();
		delete hd;
		return ret;
	}
	case ast::tree::FN:
	{
		for (const auto& arg : T->args)
		{
			if (arg->key != "return")
			{
				delete process(arg, def);
			}
			else
			{
				return process(arg, def);
			};
		}
		return nullptr;
	}
	case ast::tree::EXEC:
	{
		variable* _this = process(T->left, def);
		std::vector<variable*> c;
		for (const auto& arg : T->args)
			c.push_back(process(arg, def));
		auto _ret = _this->get()->execute(c);
		for (const auto& m : c)
			delete m;
		delete _this;
		return _ret;
	}
	case ast::tree::NOT:
	{
		return process(T->right, def)->get()->_NOT();
	}
	case ast::tree::CHEN:
	{
		return process(T->right, def)->get()->_CHEN(process(T->left, def));
	}
	case ast::tree::CHU:
	{
		return process(T->right, def)->get()->_CHU(process(T->left, def));
	}
	case ast::tree::PLUS:
	{
		return process(T->right, def)->get()->_PLUS(process(T->left, def));
	}
	case ast::tree::MINUS:
	{
		return process(T->right, def)->get()->_MINUS(process(T->left, def));
	}
	case ast::tree::EQUAL:
	{
		auto a = process(T->left, def);
		auto b = process(T->right, def);
		a->copy_value(b);
		delete a;
		delete b;
		return nullptr;
	}
	case ast::tree::IF:
	{
		const auto tmp_condition = process(T->right, def);
		if (tmp_condition != nullptr)
			if (GET_TYPE("bool", root_bool, tmp_condition->get())->access())
			{
				delete tmp_condition;
				return process(T->args[0], def);
			}
		delete tmp_condition;
		return process(T->args[1], def);
	}
	case ast::tree::WHILE:
	{
		variable* condition = nullptr;
		for (condition = process(T->right, def); condition != nullptr
			? GET_TYPE("bool", root_bool, condition->get())->access()
			: false; condition = process(T->right, def))
		{
			delete condition;
			for (const auto& arg : T->args)
			{
				if (arg->key != "return")
				{
					delete process(arg, def);
				}
				else
				{
					return process(arg, def);
				};
			}
		}
		delete condition;
		return nullptr;
	}
	default:
	{
		ERR("Oh my god,it's impossible!");
		std::terminate();
	}
	}
}