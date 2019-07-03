#include "tools.h"
#include <algorithm>
#include <iostream>

std::vector<std::string> stropr::split_string(const std::string& s, const std::string& c)
{
	std::vector<std::string> v;
	std::string::size_type pos2 = s.find(c);
	std::string::size_type pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

std::string stropr::dig(std::string& data, const char& start, const char& end)
{
	//std::cout << data << "~";
	auto _start = find(data, start);
	if (_start > data.size())
		return "";
	size_t _end;
	for (_end = _start; _end < data.size() && data[_end] != end;)
	{
		if (data[_end] == '"')
			_end = data.substr(_end + 1).find_first_of('"') + _end + 1;
		else if (data[_end] == '(') {
			for (size_t counter = 0; _end < data.size(); _end++)
			{
				if (data[_end] == '"')
					_end = data.substr(_end + 1).find_first_of('"') + _end + 1;
				if (data[_end] == '(')
					counter++;
				else if (data[_end] == ')')
					counter--;
				if (counter == 0 && data[_end] == ')')
				{
					break;
				}
			}
			//_end = data.substr(_end + 1).find_first_of(')') + _end + 1;
		}
	}
	//auto _end = find(data.substr(_start), end) + _start;
	auto tmp = data.substr(_start + 1, _end - _start - 1);
	data.erase(_start, _end - _start + 1);
	//std::cout << _start << "~" << _end << "~" << data << "~" << tmp << std::endl;
	return tmp;
}
std::vector<std::string> stropr::merge(const std::vector<std::string>& args, const std::string& de)
{
	std::vector<std::string> buf_;
	for (const auto& arg : args)
	{
		if (buf_.empty())
		{
			buf_.push_back(arg);
			continue;
		}
		auto x = buf_[(buf_.size() - 1)];
		std::string cleaned = arg;
		//TODO:Rebuild
		while (cleaned.find('"') != std::string::npos)
		{
			auto tmp = cleaned.substr(0, cleaned.find_first_of('"'));
			auto tmp2 = cleaned.substr(cleaned.substr(cleaned.find_first_of('"') + 1).find_first_of('"') + cleaned.find_first_of('"') + 2);
			cleaned = tmp + tmp2;
		}
		if ((std::count(cleaned.begin(), cleaned.end(), '(') != std::count(cleaned.begin(), cleaned.end(), ')')) || std::count(x.begin(), x.end(), '"') % 2 != 0)
		{
			x.append(de + arg);
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
size_t stropr::find_not_alphabet(const std::string& raw)
{
	for (size_t i = 0; i < raw.length(); i++)
	{
		char key = raw[i];
		if (!('a' <= key && key <= 'z' || 'A' <= key && key <= 'Z' || key == '"'))
			return i;
	}
	return std::string::npos;
}

std::string stropr::clean_str(std::string raw)
{
	while (raw.empty() ? false : raw.at(0) < 33)
		raw.erase(raw.begin());		//ÆþÍ·
	while (raw.empty() ? false : raw.at(raw.length() - 1) < 33)
		raw.erase(raw.end() - 1);		//È¥Î²
	return raw;
}
size_t stropr::find_alphabet(const std::string& raw)
{
	for (size_t i = 0; i < raw.length(); i++)
	{
		char key = raw[i];
		if ('a' <= key && key <= 'z' || 'A' <= key && key <= 'Z')
			return i;
	}
	return std::string::npos;
}
size_t stropr::find(const std::string& raw, char obj)
{
	for (size_t i = 0; i < raw.size();)
	{
		if (raw[i] == '"')
			i = raw.substr(i + 1).find_first_of('"') + i + 2;
		else if (raw[i] == '(') {
			if (obj == '(')
				return i;
			for (size_t counter = 0; i < raw.size(); i++)
			{
				if (raw[i] == '"')
					i = raw.substr(i + 1).find_first_of('"') + i + 1;
				if (raw[i] == '(')
					counter++;
				else if (raw[i] == ')') {
					if (obj == ')')
						return i;
					counter--;
				}
				if (counter == 0 && raw[i] == ')')
				{
					break;
				}
			}
			//_end = data.substr(_end + 1).find_first_of(')') + _end + 1;
		}
		else
		{
			if (obj == raw[i])
				return i;
			i++;
		}
	}
	return std::string::npos;
}
size_t stropr::find_last(const std::string& raw, char find)
{
	for (size_t i = raw.size() - 1; i > 0;)
	{
		if (raw[i] == '"')
		{
			i = raw.substr(0, i - 1).find_last_of('"') - 1;
		}
		//else  if (raw[i] == ')')
		//{
		//	i = raw.substr(0, i - 1).find_last_of('(') - 1;
		//}
		else
		{
			if (find == raw[i])
				return i;
			i--;
		}
		if (i > raw.size())
			i = 0;
	}
	return std::string::npos;
}
std::vector<std::string> stropr::split_to_two_part(const std::string& source, char c)
{
	size_t mid = find_last(source, c);
	std::vector<std::string> buf;
	buf.push_back(source.substr(0, mid));
	buf.push_back(source.substr(std::min(source.size(), mid + 1)));
	return buf;
}