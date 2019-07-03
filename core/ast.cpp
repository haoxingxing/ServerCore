#include "ast.h"
#include "domain.h"
#include "exception.h"
#include <algorithm>
#include "tools.h"
std::vector<std::string> ast::split(const std::string& raw /*取新鲜活虾一篮*/)
{
	std::vector<std::string> r; //准备好盘子
	auto v = stropr::split_string(raw, ";");  //一只一只摆好
	for (auto m : v)
	{
		while (m.find('#') != std::string::npos) {
			if (m.find('\n') != std::string::npos)
			{
				m = m.substr(m.find_first_of('\n') + 1); //去除污泥等杂物
			}
			else
			{
				m = stropr::split_string(m, "#")[0]; //去除污泥等杂物 * 2
			}
		}
		m = stropr::clean_str(m);
		if (m.empty())
			continue;  //没肉的不要
		r.push_back(m); //摆摆好
	}
	return stropr::merge(r, ";");//送到厨房
}

bool ast::find_start_key(const std::string& s)
{
	return s == "if" || s == "while";
}
bool ast::find_end_key(const std::string& s)
{
	return s == "end";
}
// t=true
ast::tree* ast::find_method(std::string& raw)
{
	if (stropr::find(raw, '=') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '=');
		return new tree(tree::_operation::EQUAL, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '*') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '*');
		return new tree(tree::_operation::CHEN, "", {}, find_method(x[0]), find_method(x[1]));
	}
	if (stropr::find(raw, '/') != std::string::npos)
	{
		auto x = stropr::split_to_two_part(raw, '/');
		return new tree(tree::_operation::CHU, "", {}, find_method(x[0]), find_method(x[1]));
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
		auto x = stropr::find(raw, '!');
		return new tree(tree::_operation::NOT, "", {}, nullptr, find_method(raw.substr(x + 1)));
	}
	if (stropr::find(raw, '(') != std::string::npos && stropr::find(raw, ')') != std::string::npos)
	{
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

ast::tree* ast::analysis(const std::vector<std::string>& raw  /* 送来的干净的虾 */)
{
	//TODO: cout("Hello World\n")
	//TODO: t=true
	//TODO: cout(!t)
	//return new tree("1", "1");
	return nullptr;
}