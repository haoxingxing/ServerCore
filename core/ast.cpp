#include "ast.h"
#include "domain.h"
#include "exception.h"
#include <algorithm>
#include <utility>
#include "tools.h"
int ast::tree::counter = 0;
std::vector<std::string> ast::split(const std::string& raw)
{
	std::vector<std::string> r;
	auto v = stropr::split_string(raw, ";");
	for (auto m : v)
	{
		while (m.find('#') != std::string::npos) {
			if (m.find('\n') != std::string::npos)
			{
				m = m.substr(m.find_first_of('\n') + 1);
			}
			else
			{
				m = stropr::split_string(m, "#")[0];
			}
		}
		m = stropr::clean_str(m);
		if (m.empty())
			continue;
		r.push_back(m);
	}
	return stropr::merge(r, ";");
}

bool ast::find_start_key(const std::string& s)
{
	return s == "if" || s == "while";
}
bool ast::find_end_key(const std::string& s)
{
	return s == "end";
}
ast::tree* ast::find_method(std::string raw)
{
	if (stropr::find(raw, "&&") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, "&&");
		return new tree(tree::_operation::AND, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, "||") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, "||");
		return new tree(tree::_operation::OR, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, "==") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, "==");
		return new tree(tree::_operation::EQUAL, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, "!=") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, "!=");
		return new tree(tree::_operation::NOT_EQUAL, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, ">=") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, ">=");
		return new tree(tree::_operation::MORE_EQUAL, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, "<=") != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, "<=");
		return new tree(tree::_operation::LESS_EQUAL, "", {}, find_method(x[0]), find_method(x[1]));
	}

	if (stropr::find(raw, '=') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '=');
		return new tree(tree::_operation::MAKE, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '>') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '>');
		return new tree(tree::_operation::MORE, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '<') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '<');
		return new tree(tree::_operation::LESS, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '*') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '*');
		return new tree(tree::_operation::MULTIPLY, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '/') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '/');
		return new tree(tree::_operation::DIVISION, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '+') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '+');
		return new tree(tree::_operation::PLUS, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '-') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '-');
		return new tree(tree::_operation::MINUS, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '!') != std::string::npos)
	{
		return new tree(tree::_operation::NOT, "", {}, nullptr, find_method(raw.substr(stropr::find(raw, '!') + 1)));
	}
	if (stropr::find(raw, '(') != std::string::npos && stropr::find(raw, ')') != std::string::npos)
	{
		if (raw[0] == '(' && raw[raw.size() - 1] == ')')
			return find_method(stropr::dig(raw));
		auto args = stropr::merge(stropr::split_string(stropr::dig(raw, '(', ')'), ","), ",");
		std::vector<tree*> t;
		t.reserve(args.size());
		for (auto& n : args)
		{
			t.push_back(find_method(n));
		}
		return new tree(tree::_operation::EXEC, "", t, find_method(raw));
	}

	if (stropr::find(raw, '.') != std::string::npos)
	{
		/*a = "=b"*/
		auto x = stropr::split_to_two_part(raw, '.');
		return new tree(tree::_operation::DOT, "", {}, find_method(x[0]), find_method(x[1]));
	}
	return new ast::tree(tree::EMPTY, raw, {});
}

ast::tree::tree(_operation __operation, std::string _key, std::vector<tree*> _args, tree* _left, tree* _right) :
	left(_left), right(_right), args(std::move(_args)), key(std::move(_key)), operation(__operation)
{
	counter++;
}
ast::tree* ast::analysis(const std::vector<std::string>& _raw)
{
	std::vector<std::string> raw = _raw;
	tree* root = new tree(tree::_operation::FN, "function", {});
	for (size_t i = 0; i < raw.size(); i++)
	{
		std::string verify_head = raw[i].substr(0, stropr::find_not_alphabet(raw[i]));
		SWITCH_BEGIN(verify_head)
			SWITCH_CASE("if")
		{
			tree* if_body = new tree(tree::IF, "if-body", {}, nullptr, find_method(raw[i].substr(2)));
			std::vector<std::string> ift, else_body, * hd = &ift;
			size_t start_counter = 0, end_counter = 0;
			for (size_t find = i + 1; find < raw.size(); find++)
			{
				auto key = raw[find].substr(0, stropr::find_not_alphabet(raw[find]));
				if (find_start_key(key))
				{
					start_counter += 1;
				}
				if (find_end_key(key))
				{
					if (end_counter == start_counter) {
						i = find;
						break;
					}
					end_counter++;
				}
				if (key == "else" && end_counter == start_counter)
					hd = &else_body;
				else
					hd->push_back(raw[find]);
			}
			if_body->args.push_back(analysis(ift));
			if_body->args.push_back(analysis(else_body));
			root->args.push_back(if_body);
		}
		SWITCH_CASE("while")
		{
			tree* while_body = new tree(tree::WHILE, "while-body", {}, nullptr, find_method(raw[i].substr(5)));
			std::vector<std::string> body;
			size_t start_counter = 0, end_counter = 0;
			for (size_t find = i + 1; find < raw.size(); find++)
			{
				auto key = raw[find].substr(0, stropr::find_not_alphabet(raw[find]));
				if (find_start_key(key))
				{
					start_counter += 1;
				}
				if (find_end_key(key))
				{
					if (end_counter == start_counter) {
						i = find;
						break;
					}
					end_counter++;
				}
				body.push_back(raw[find]);
			}
			while_body->args.push_back(analysis(body));
			root->args.push_back(while_body);
		}
		SWITCH_DEFAULT{
			root->args.push_back(find_method(raw[i]));
		}
			SWITCH_END
	}
	return root;
}