#include "database.h"
#include <sstream>
#include <algorithm>
#include "ServerCore.h"
#include "file.h"

database::database()
{
	DEB(print_pointer(this));
}

database::~database()
{
	std::for_each(_data.begin(), _data.end(), [&](std::pair<std::string, data_container*> d) {
		delete d.second;
		});
	DEB(print_pointer(this));
}

void database::insert(const std::string& key, data_container* value)
{
	if (_data.find(key) != _data.end())
	{
		WARN(TS_ID_5 " [" + key + "]," TS_ID_6);
		this->remove(key);
	}
	DEB(TS_ID_7" [" + key + "," + print_pointer(value) + "]");
	_data.insert(std::make_pair(key, value));
	SUCC("");
}

void database::remove(const std::string & key)
{
	DEB(TS_ID_6" [" + key + "]");
	if (_data.find(key) != _data.end())
	{
		delete _data[key];
		_data.erase(_data.find(key));
		SUCC("");
	}
	else
	{
		WARN(TS_ID_4);
	}
}

data_container* database::get(const std::string & key)
{
	DEB(TS_ID_8 " [" + key + "]");
	if (_data.find(key) != _data.end())
	{
		SUCC("");
		return _data.at(key);
	}
	else
	{
		ERR(TS_ID_4);
		WARN(TS_ID_9);
		this->insert(key, new data_container("void"));
		return get(key);
	}
}


std::vector<std::string> database::SplitString(const std::string & s, const std::string & c)
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

std::string database::str_to_hex(const std::string & s, bool upper)
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
std::string database::hex_to_str(const std::string & hex)
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