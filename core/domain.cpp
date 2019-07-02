#include <sstream>
#include <algorithm>
#include <utility>
#include "core.h"
#include "domain.h"

domain::domain()
{
	DEB(PRINT_POINTER(this));
}

domain::~domain()
{
	std::for_each(_data.begin(), _data.end(), [&](const std::pair<std::string, variable*> & d) {
		delete d.second;
		});
	DEB(PRINT_POINTER(this));
}
void domain::insert(const std::string& key, variable* value)
{
	if (_data.find(key) != _data.end())
	{
		DEB(TS_ID_5 " [" + key + "]," TS_ID_6);
		this->remove(key);
	}
	DEB(TS_ID_7" [" + key + "," + PRINT_POINTER(value) + "]");
	_data.insert(std::make_pair(key, value));
}

void domain::remove(const std::string & key)
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

variable* domain::get(const std::string & key)
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
		this->insert(key, new variable());
		return get(key);
	}
}

