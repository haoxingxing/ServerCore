#include "database.h"
_database::_database(bool _isfile, std::string filename) :isfile(_isfile)
{
	DEB(print_pointer(this));
	if (isfile)
	{
		fp = new File(filename);
	}
	else
	{
		fp = nullptr;
	}
}

_database::~_database()
{
	if (isfile)
	{
		delete fp;
	}
	std::for_each(data.begin(), data.end(), [&](std::pair<std::string, _data*> d) {
		delete d.second;
		});
	DEB(print_pointer(this));
}

void _database::insert(const std::string& key, _data* value)
{
	if (data.find(key) != data.end())
	{
		WARN(TS_ID_5 " [" + key + "]," TS_ID_6);
		this->remove(key);
	}
	DEB(TS_ID_7" [" + key + "," + print_pointer(value) + "]");
	data.insert(std::make_pair(key, value));
	SUCC("");
}

void _database::remove(const std::string & key)
{
	DEB(TS_ID_6" [" + key + "]");
	if (data.find(key) != data.end())
	{
		delete data[key];
		data.erase(data.find(key));
		SUCC("");
	}
	else
	{
		WARN(TS_ID_4);
	}
}

_data* _database::get(const std::string & key)
{
	DEB(TS_ID_8 " [" + key + "]");
	if (data.find(key) != data.end())
	{
		SUCC("");
		return data.at(key);
	}
	else
	{
		ERR(TS_ID_4);
		WARN(TS_ID_9);
		this->insert(key, new _data("void"));
		return get(key);
	}
}

_data* _database::operator[](const std::string & key)
{
	return this->get(key);
}

std::string _database::map_to_str()
{
	std::string buf = create_database_string();
	std::for_each(data.begin(), data.end(), [&](std::pair<std::string, _data*> d) {
		str_insert(buf, d.first, d.second);
		});
	return buf;
}

std::map<std::string, _data*> _database::data_()
{
	return data;
}

bool _database::contains(const std::string & key)
{
	if (data.find(key) != data.end())
		return true;
	else
		return false;
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

void _database::str_to_map(const std::string & str)
{
//	if (str.size() > 0)
//	{
//		if (str.at(0) != DB_START) {
//			ERR(TS_ID_1);
//			return;
//		}
//	}
//	else
//	{
//		ERR(TS_ID_1);
//		return;
//	}
//	std::vector<std::string> v = SplitString(str, "|");
//	for (size_t i = 1; i < v.size(); ++i)
//	{
//		if (v[i].find('@') == std::string::npos)
//		{
//			WARN(TS_ID_2);
//			continue;
//		}
//		std::vector<std::string> b = SplitString(v[i], "@");
//		switch (b[1].at(0))
//		{
//		case '#':
//			insert(hex_to_str(b[0]), new _data(std::stoi(b[1].substr(1, b[1].length() - 1))));
//			break;
//		case '$':
//			insert(hex_to_str(b[0]), new _data(std::stoi(b[1].substr(1, b[1].length() - 1)) != 0));
//			break;
//		case '%':
//			insert(hex_to_str(b[0]), new _data(hex_to_str(b[1].substr(1, b[1].length() - 1))));
//			break;
//		case '&':
////			insert(hex_to_str(b[0]), new _data());
//			break;
//		default:
//			WARN(TS_ID_3);
//			break;
//		}
//	}
}

std::string _database::str_to_hex(const std::string & s, bool upper)
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
	str_to_map(fp->read());
}

void _database::writetofile()
{
	fp->write(map_to_str());
}

void _database::str_insert(std::string & str, const std::string & key, _data * d)
{
	//if (str.at(0) != DB_START)
	//{
	//	ERR(TS_ID_1);
	//	return;
	//}
	//str += '|';
	//str += str_to_hex(key);
	//str += '@';
	//switch (d->what()) {
	//case _data::Int:
	//	str += '#';
	//	str += std::to_string(d->getInt().second);
	//	break;
	//case _data::Bool:
	//	str += '$';
	//	str += std::to_string(d->getBool().second);
	//	break;
	//case _data::String:
	//	str += '%';
	//	str += str_to_hex(d->getString().second);
	//	break;
	//case _data::Void:
	//	str += '&';
	//	break;
	//};
}

std::string _database::create_database_string()
{
	return std::string() + DB_START;
}

_data::_data(std::string _type) :type(_type)
{
}

string::string(const std::string & v) : _data("string")
{
	data = v;
}