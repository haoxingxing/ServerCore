#include "database.h"
_database::_database(bool _isfile, std::string filename) :isfile(_isfile)
{
	DEB(print_pointer(this));
	if (isfile)
	{
		fp = new File(filename);
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

void _database::insert(const std::string & key, _data* value)
{
	if (data.find(key) != data.end())
	{
		WARN("Already Exist [" + key + "],Removing");
		this->remove(key);
	}
	LOG("Inserting [" + key + "," + print_pointer(value) + "]");
	data.insert(std::make_pair(key, value));
	SUCC("");
}

void _database::remove(const std::string & key)
{
	LOG("Removing [" + key + "]");
	if (data.find(key) != data.end())
	{
		delete data[key];
		data.erase(data.find(key));
		SUCC("");
	}
	else
	{
		WARN("Not Find");
	}
}

_data* _database::get(const std::string & key)
{
	LOG("Accessing [" + key + "]");
	if (data.find(key) != data.end())
	{
		SUCC("");
		return data.at(key);
	}
	else
	{
		ERR("Not Find");
		WARN("Creating a empty data to avoid nullptr");
		this->insert(key, new _data);
		return get(key);
	}
}

_data* _database::operator[](const std::string & key)
{
	return this->get(key);
}

std::string _database::map_to_str(const std::map<std::string, _data*>& m)
{
	std::string buf = create_database_string();
	std::for_each(m.begin(), m.end(), [&](std::pair<std::string, _data*> d) {
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

std::map<std::string, _data*> _database::str_to_map(const std::string& str)
{
	std::map<std::string, _data*> buf;
	if (str.size() > 0)
	{
		if (str.at(0) != '\u0001') {
			ERR("Invalid Database String");
			return buf;
		}
	}
	else
	{
		ERR("Invalid Database String");
		return buf;
	}
	std::vector<std::string> v = SplitString(str, "|");
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i].find('@') == std::string::npos)
		{
			WARN("Invalid Group");
			continue;
		}
		std::vector<std::string> b = SplitString(v[i], "@");
		switch (b[1].at(0))
		{
		case '#':
			buf.insert(std::make_pair(hex_to_str(b[0]), new _data(std::stoi(b[1].substr(1, b[1].length() - 1)))));
			break;
		case '$':
			buf.insert(std::make_pair(hex_to_str(b[0]), new _data(std::stoi(b[1].substr(1, b[1].length() - 1)) != 0)));
			break;
		case '%':
			buf.insert(std::make_pair(hex_to_str(b[0]), new _data(hex_to_str(b[1].substr(1, b[1].length() - 1)))));
			break;
		case '&':
			buf.insert(std::make_pair(hex_to_str(b[0]), new _data()));
			break;
		default:
			WARN("Invalid Type");
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
	data = str_to_map(fp->read());
}

void _database::writetofile()
{
	fp->write(map_to_str(data));
}

void _database::str_insert(std::string & str, const std::string& key, _data* d)
{
	if (str.at(0) != '\u0001')
	{
		ERR("Invalid Database String");
		return;
	}
	str += '|';
	str += str_to_hex(key);
	str += '@';
	switch (d->what()) {
	case _data::Int:
		str += '#';
		str += std::to_string(d->getInt().second);
		break;
	case _data::Bool:
		str += '$';
		str += std::to_string(d->getBool().second);
		break;
	case _data::String:
		str += '%';
		str += str_to_hex(d->getString().second);
		break;
	case _data::Void:
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
	DEB(print_pointer(this));
}

_data::_data(const char * st)
{
	setValue(st);
	DEB(print_pointer(this));
}

_data::_data(const std::string & st)
{
	setValue(st);
	DEB(print_pointer(this));
}

_data::_data(bool b)
{
	setValue(b);
	DEB(print_pointer(this));
}

_data::_data()
{
	clearValue();
	DEB(print_pointer(this));
}

_data::~_data()
{
	clearValue();
	DEB(print_pointer(this));
}

void _data::setValue(int i)
{
	clearValue();
	s = Int;
	d.i = i;
}

void _data::setValue(const char * st)
{
	clearValue();
	s = String;
	d.str = new std::string(st);
}

void _data::setValue(const std::string &st)
{
	clearValue();
	s = String;
	d.str = new std::string(st);
}

void _data::setValue(bool b)
{
	clearValue();
	s = Bool;
	d.boolean = b;
}

void _data::clearValue()
{
	if (s == String)
		delete d.str;
	s = Void;
}

_data::status _data::what()
{
	return s;
}

std::pair<bool, int> _data::getInt()
{
	return std::pair<bool, int>(s == Int, (s == Int) ? d.i : 0);
}

std::pair<bool, std::string> _data::getString()
{
	return std::pair<bool, std::string>(s == String, (s == String) ? *d.str : std::string());
}

std::pair<bool, bool> _data::getBool()
{
	return std::pair<bool, bool>(s == Bool, (s == Bool) ? d.boolean : false);
}