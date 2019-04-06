#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "file.h"
#include "log.h"
#define data_file "data"

class _data {
public:
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
	void setValue(int i);
	void setValue(const char *);
	void setValue(const std::string&);
	void setValue(bool b);
	void clearValue();
	_data::status what();
	std::pair<bool, int> getInt();
	std::pair<bool, std::string> getString();
	std::pair<bool, bool> getBool();
};

static class _database {
public:
	_database(std::string filename);
	~_database();

	static std::string create_database_string();
	static void str_insert(std::string& str, const std::string& key, _data&);
private:
	static std::string str_to_hex(const std::string&, bool upper = false);
	static std::string map_to_str(const std::map<std::string, _data> &);
	static std::string hex_to_str(const std::string&);
	void loadfromfile();
	void writetofile();

	File *fp;
	std::map<std::string, _data> data;
} database(data_file);

#endif // DATABASE_H
