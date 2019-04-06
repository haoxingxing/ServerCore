#include "database.h"
_database::_database(std::string filename)
{
	fp = new File(filename);
}

_database::~_database()
{
	delete fp;
}

std::string _database::map_to_str(const std::map<std::string, _data>& m)
{
	std::string buf = create_database_string();
	std::for_each(m.begin(), m.end(), [&](std::pair<std::string, _data> d) {
		str_insert(buf, d.first, d.second);
	});
	return buf;
}

std::vector<std::string> _database::SplitString(const std::string & s, const std::string & c)
{
	std::vector<std::string> v;
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
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

std::map<std::string, _data> _database::str_to_map(const std::string& str)
{
	std::map<std::string, _data> buf;
	if (str.at(0) != '\u0001')
	{
		log::print(log::Error, "Invalid Database String");
		return buf;
	}
	std::vector<std::string> v = SplitString(str, "|");
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i].find('@') == std::string::npos)
		{
			log::print(log::Warning, "Invalid Group");
			break;
		}
		std::vector<std::string> b = SplitString(v[i], "@");
		switch (b[1].at(0))
		{
		case '#':
			buf.insert(std::make_pair(hex_to_str(b[0]), _data(std::stoi(b[1].substr(1, b[1].length() - 1)))));
			break;
		case '$':
			buf.insert(std::make_pair(hex_to_str(b[0]), _data(std::stoi(b[1].substr(1, b[1].length() - 1)) != 0)));
			break;
		case '%':
			buf.insert(std::make_pair(hex_to_str(b[0]), _data(hex_to_str(b[1].substr(1, b[1].length() - 1)))));
			break;
		case '&':
			buf.insert(std::make_pair(hex_to_str(b[0]), _data()));
			break;
		default:
			log::print(log::Warning, "Invalid Type");
			break;
		}
	}
	return buf;
}

std::string _database::str_to_hex(const std::string& s, bool upper)
{
	std::ostringstream ret;

	unsigned int c;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		c = (unsigned int)(unsigned char)s[i];
		ret << std::hex << std::setfill('0') <<
			std::setw(2) << (upper ? std::uppercase : std::nouppercase) << c;
	}
	return ret.str();
}
std::string _database::hex_to_str(const std::string & hex)
{
	size_t len = hex.length();
	std::string newString;
	for (size_t i = 0; i < len; i += 2)
	{
		std::string byte = hex.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
		newString.push_back(chr);
	}
	return newString;
}

void _database::loadfromfile()
{
}

void _database::writetofile()
{
}

void _database::str_insert(std::string & str, const std::string& key, _data & d)
{
	if (str.at(0) != '\u0001')
	{
		log::print(log::Error, "Invalid Database String");
		return;
	}
	str += '|';
	str += str_to_hex(key);
	str += '@';
	switch (d.what()) {
	case _data::INT:
		str += '#';
		str += std::to_string(d.getInt().second);
		break;
	case _data::BOOL:
		str += '$';
		str += std::to_string(d.getBool().second);
		break;
	case _data::STRING:
		str += '%';
		str += str_to_hex(d.getString().second);
		break;
	case _data::NONE:
		str += '&';
		break;
	};
}

std::string _database::create_database_string()
{
	return std::string("\u0001");
}

_data::_data(int i)
{
	setValue(i);
}

_data::_data(const char * st)
{
	setValue(st);
}

_data::_data(const std::string & st)
{
	setValue(st);
}

_data::_data(bool b)
{
	setValue(b);
}

_data::_data()
{
	clearValue();
}

void _data::setValue(int i)
{
	clearValue();
	s = INT;
	d.i = i;
}

void _data::setValue(const char * st)
{
	clearValue();
	s = STRING;
	d.str = new std::string(st);
}

void _data::setValue(const std::string &st)
{
	clearValue();
	s = STRING;
	d.str = new std::string(st);
}

void _data::setValue(bool b)
{
	clearValue();
	s = BOOL;
	d.boolean = b;
}

void _data::clearValue()
{
	if (s == STRING)
		delete d.str;
	s = NONE;
}

_data::status _data::what()
{
	return s;
}

std::pair<bool, int> _data::getInt()
{
	return std::pair<bool, int>(s == INT, (s == INT) ? d.i : 0);
}

std::pair<bool, std::string> _data::getString()
{
	return std::pair<bool, std::string>(s == STRING, (s == STRING) ? *d.str : std::string());
}

std::pair<bool, bool> _data::getBool()
{
	return std::pair<bool, bool>(s == BOOL, (s == BOOL) ? d.boolean : false);
}