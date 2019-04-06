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

class _data {
public:
	_data(int i);
	_data(const char *st);
	_data(const std::string&st);
	_data(bool b);
	_data();
	~_data();
	void setValue(int i);
	void setValue(const char *);
	void setValue(const std::string&);
	void setValue(bool b);
	union _datas
	{
		int i;
		std::string *str;
		bool boolean;
	}d;
	enum status
	{
		INT,
		STRING,
		BOOL,
		NONE
	}s = NONE;
	void clearValue();
	_data::status what();
	std::pair<bool, int> getInt();
	std::pair<bool, std::string> getString();
	std::pair<bool, bool> getBool();
};

class _database {
public:
	_database(std::string filename = data_file);
	~_database();
	// Insert a element
	void insert(const std::string& key, _data* value);
	// Remove a element
	void remove(const std::string& key);
	// Access a element
	_data* get(const std::string& key);
	// Access a element
	_data* operator[](const std::string& key);

	static std::vector<std::string> SplitString(const std::string& s, const std::string& c);
private:
	// Convert a element into the string database
	static void str_insert(std::string& str, const std::string& key, _data*);
	// Create a database string
	static std::string create_database_string();
	// Convert database to string
	static std::string map_to_str(const std::map<std::string, _data*> &);
	// Convert string to database
	static std::map<std::string, _data*> str_to_map(const std::string &str);
	// Convert string to hex string
	static std::string str_to_hex(const std::string&, bool upper = false);
	// Convert hex string to string
	static std::string hex_to_str(const std::string&);
	// Load database from file
	void loadfromfile();
	// Write database to file
	void writetofile();

	File *fp;
	std::map<std::string, _data*> data;
};

extern _database database;
#endif // DATABASE_H
