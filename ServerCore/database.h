#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
#include "file.h"
#include "log.h"
#include "ServerCore.h"
/* Check A Type of Element
 * d: a _data var
 * t: Type in _data::status
 *		Int
 *		String
 *		Bool
 *		Void
 */
#define if_type_is(d,t) (((d->what())==(_data::t)))
class _data {
public:
	_data(std::string _type);
	virtual std::string what() {
		return type;
	};
	virtual _data* copy() { return nullptr; };
private:
	std::string type;
};

class string : public _data {
public:
	string(const std::string& v);
	operator std::string& () {
		return data;
	}
private:
	std::string data;
};

class _database {
public:
	_database(bool isfile = false, std::string filename = "");
	virtual ~_database();
	// Insert a element
	virtual void insert(const std::string& key, _data* value);
	// Remove a element
	virtual	void remove(const std::string& key);
	// Access a element
	virtual _data* get(const std::string& key);
	// Access a element
	virtual _data* operator[](const std::string& key);
	// Load database from file
	virtual void loadfromfile();
	// Write database to file
	virtual void writetofile();
	// Get Whole data map
	virtual std::map<std::string, _data*> data_();
	// Find if a key exists
	virtual bool contains(const std::string& key);

	static std::vector<std::string> SplitString(const std::string& s, const std::string& c);
protected:
	// Convert a element into the string database
	virtual void str_insert(std::string& str, const std::string& key, _data*);
	// Create a database string
	virtual std::string create_database_string();
	// Convert database to string
	virtual std::string map_to_str();
	// Convert string to database
	virtual void str_to_map(const std::string& str);
	// Convert string to hex string
	static std::string str_to_hex(const std::string&, bool upper = false);
	// Convert hex string to string
	static std::string hex_to_str(const std::string&);
	File* fp;
	std::map<std::string, _data*> data;
	bool isfile;
};
#endif // DATABASE_H
