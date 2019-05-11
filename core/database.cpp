#include "database.h"
#include <sstream>
#include <algorithm>
#include <utility>
#include "core.h"
#include "basic_types.h"
data::data(std::string type, const data* parent) : type(std::move(type))
{
	DEB(print_pointer(this));
	member = parent == nullptr ? [&]() {is_member_own = true; return new database; }() : [&]() {is_member_own = false; return parent->member; }();
}
data::~data()
{
	if (is_member_own)
		delete member;
	DEB(print_pointer(this));
}
data_container* data::access_member(const std::string& name)
{
	return member->get(name);
}
std::shared_ptr<data_container> data::convert_type(const std::string&)
{
	return std::make_shared<data_container>();
}
database::database()
{
	DEB(print_pointer(this));
}

database::~database()
{
	std::for_each(_data.begin(), _data.end(), [&](const std::pair<std::string, data_container*> & d) {
		delete d.second;
		});
	DEB(print_pointer(this));
}

void database::insert(const std::string& key, data_container* value)
{
	if (_data.find(key) != _data.end())
	{
		DEB(TS_ID_5 " [" + key + "]," TS_ID_6);
		this->remove(key);
	}
	DEB(TS_ID_7" [" + key + "," + print_pointer(value) + "]");
	_data.insert(std::make_pair(key, value));
}

void database::remove(const std::string & key)
{
	DEB(TS_ID_6" [" + key + "]");
	if (_data.find(key) != _data.end())
	{
		delete _data[key];
		_data.erase(_data.find(key));
	}
	else
	{
		DEB(TS_ID_4" [" + key + "]");
	}
}

data_container* database::get(const std::string & key)
{
	DEB(TS_ID_8 " [" + key + "]");
	if (_data.find(key) != _data.end())
	{
		return _data.at(key);
	}
	else
	{
		DEB(TS_ID_4" [" + key + "]");
		DEB(TS_ID_9);
		this->insert(key, new data_container());
		return get(key);
	}
}

std::vector<std::string> database::SplitString(const std::string & s, const std::string & c)
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