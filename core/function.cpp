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
		if (def->contains(T->key))
			return def->get(T->key)->copy();
		if (T->key.empty()) {
			auto* hd = new variable((new root_void())->new_this());
			def->insert(T->key, hd);
			return hd->copy();
		}
		if (std::find_if(T->key.begin(), T->key.end(), [](char c) { return !std::isdigit(c); }) == T->key.end()) {
			auto* hd = new variable((new root_int(std::stoi(T->key)))->new_this());
			def->insert(T->key, hd);
			return hd->copy();
		}
		if (T->key.find('"') != std::string::npos) {
			auto x = T->key.substr(1).substr(0, T->key.size() - 2);
			x = stropr::ReplaceAll(x, "\\n", "\n");
			x = stropr::ReplaceAll(x, "\\r", "\r");
			auto* hd = new variable((new root_string(x))->new_this());
			def->insert(T->key, hd);
			return hd->copy();
		}
		if (T->key == "true" || T->key == "false") {
			auto* hd = new variable((new root_bool(T->key == "true"))->new_this());
			def->insert(T->key, hd);
			return hd->copy();
		}
		if (T->key.find('\'') != std::string::npos) {
			auto* hd = new variable((new root_char(T->key.length() < 3 ? char(0) : (T->key.substr(1).substr(0, T->key.size() - 2).at(0))))->new_this());
			def->insert(T->key, hd);
			return hd;
		}
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
		//def->insert("_returned_this",_this);
		std::vector<variable*> c;
		for (const auto& arg : T->args)
			c.push_back(process(arg, def));

		auto _ret = _this->get()->execute(c);
		for (const auto& m : c) {
			delete m;
		}
		delete _this;
		return _ret;
	}
	case ast::tree::NOT:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", {}, new ast::tree(ast::tree::DOT, "", {}, T->right, new ast::tree(ast::tree::EMPTY, "!", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		delete tmp;
		return ret;
	}
	case ast::tree::MULTIPLY:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "*", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::DIVISION:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "/", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::PLUS:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "+", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MINUS:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "-", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MORE:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, ">", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::LESS:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "<", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "==", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MORE_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, ">=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::PLUS_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "+=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MINUS_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "-=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::DIVISION_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "/=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MULTIPLY_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, ">=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::LESS_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "<=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::AND:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "&&", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::NOT_EQUAL:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "!=", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::OR:
	{
		ast::tree* tmp = new ast::tree(ast::tree::EXEC, "", { T->right }, new ast::tree(ast::tree::DOT, "", {}, T->left, new ast::tree(ast::tree::EMPTY, "||", {})));;
		auto ret = process(tmp, def);
		tmp->left->left = nullptr;
		tmp->args.clear();
		delete tmp;
		return ret;
	}
	case ast::tree::MAKE:
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
		variable* condition;
		for (condition = process(T->right, def); condition != nullptr
			? GET_TYPE("bool", root_bool, condition->get())->access()
			: false; condition = process(T->right, def))
		{
			delete condition;
			auto ret = process(T->args[0], def);
			if (ret != nullptr)
				return ret;
			delete ret;
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