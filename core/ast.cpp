#include "ast.h"
#include "domain.h"
#include "exception.h"

std::vector<std::string> ast::split(const std::string& raw /*取新鲜活虾一篮*/)
{
	std::vector<std::string> r; //准备好盘子
	auto v = domain::SplitString(raw, ";");  //一只一只摆好
	for (auto m : v)
	{
		while (m.find('#') != std::string::npos) {
			if (m.find('\n') != std::string::npos)
			{
				m = m.substr(m.find_first_of('\n') + 1); //去除污泥等杂物
			}
			else
			{
				m = domain::SplitString(m, "#")[0]; //去除污泥等杂物 * 2
			}
		}
		m = clean_str(m);
		if (m.empty())
			continue;  //没肉的不要
		r.push_back(m); //摆摆好
	}
	return r; //送到厨房
}
std::string ast::clean_str(std::string raw)
{
	while ((raw.empty() ? false : raw.at(0) < 33))
		raw.erase(raw.begin());		//掐头
	while ((raw.empty() ? false : raw.at(raw.length() - 1) < 33))
		raw.erase(raw.end() - 1);		//去尾
	return raw;
}
std::vector<std::string> ast::split_arg(const std::string & s)
{
	std::vector<std::string> args = domain::SplitString(s, ","), buf_;
	for (const auto& arg : args)
	{
		if (buf_.empty())
		{
			buf_.push_back(arg);
			continue;
		}
		auto x = buf_[(buf_.size() - 1)];
		if ((std::count(x.begin(), x.end(), '(') != std::count(x.begin(), x.end(), ')')) || std::count(x.begin(), x.end(), '"') % 2 != 0)
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
	return buf_;
}

ast::tree ast::analysis(const std::vector<std::string> & raw  /* 送来的干净的虾 */)
{
	/*
	 * var(x,"")
	 * x
	 * var(first,x.at(1))
	 * if(first.equals(23))
	 * echo("Equals")
	 * else
	 * echo("Not Equals")
	 * end
	 * while(first.less(128))
	 * echo(first)
	 * var(first,first.minus(1))
	 * end
	 */
	tree t; /*准备好锅*/
	for (size_t i = 0; i < raw.size();)
	{
		auto branch = raw[i];
		t.args.emplace_back();
		const auto last = t.args.size() - 1;
		//TODO: "var(test)"
		const int n_of_brackets = std::count(branch.begin(), branch.end(), '(');
		if ((n_of_brackets != std::count(branch.begin(), branch.end(), ')')) || std::count(branch.begin(), branch.end(), '"') % 2 != 0)  //看看有没有坏
			throw NEW_EXCEPT("syntax err");
		if (n_of_brackets != 0) //看看是不是活的
		{
			t.args[last].data = branch.substr(0, branch.find_first_of('(')); //看怎么煮
			std::string s = branch.substr(branch.find_first_of('(') + 1, branch.find_last_of(')') - branch.find_first_of('(') - 1);
			SWITCH_BEGIN(t.args[last].data)
				SWITCH_CASE("if")
			{
				t.args[last].args.push_back(analysis(split_arg(s)));
				t.args[last].args[t.args[last].args.size() - 1].data = "condition";
				std::vector<std::string> sli;
				size_t find;
				for (find = last + 1; find < raw.size(); find++)
				{
					if (raw[find] == "end")
						break;
					sli.push_back(raw[find]);
				}
				std::vector<std::string> if_true, if_false;
				bool has_else_appeared = false;
				for (const auto& c : sli)
				{
					if (c == "else")
					{
						has_else_appeared = true;
						continue;
					}
					(has_else_appeared ? if_false : if_true).push_back(c);
				}
				t.args[last].args.push_back(analysis(if_true));
				t.args[last].args[t.args[last].args.size() - 1].data = "true";
				t.args[last].args.push_back(analysis(if_false));
				t.args[last].args[t.args[last].args.size() - 1].data = "false";
				i = find + 1;
			}
			SWITCH_DEFAULT{
			t.args[last].args.push_back(analysis(split_arg(s)));
				i++;
			}
				SWITCH_END
		}
		else
		{
			t.args[last].data = branch;
			i++;
		}
	}
	return t;// 可以煮了
}