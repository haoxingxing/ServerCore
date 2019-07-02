#ifndef DOMAIN_H
#define DOMAIN_H
#include <map>
#include <vector>
#include <iomanip>
#include "variable.h"
class domain
{
public:
	domain();
	virtual ~domain();

	// Insert a element
	virtual void insert(const std::string& key, variable* value);
	// Remove a element
	virtual void remove(const std::string& key);
	// Access a element
	virtual variable* get(const std::string& key);
	// Access a element
	virtual variable* operator[](const std::string& key)
	{
		return get(key);
	};
	// Get Whole root map
	virtual std::map<std::string, variable*> get_data() {
		return _data;
	};
	// Find if a key exists
	virtual bool contains(const std::string& key) {
		return _data.find(key) != _data.end();
	};

protected:
	std::map<std::string, variable*> _data{};
};

#endif // DATABASE_H
