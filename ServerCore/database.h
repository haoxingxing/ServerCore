#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <iomanip>
#include "file.h"

class data_container
{
public:
	class data;
	typedef data*(*construction_handle)(std::vector<data*>);
	explicit data_container(const std::string& type = "void"):type_(type){};
	~data_container() = default;

	std::string what() const
	{
		return type_;
	};

	class data
	{
	public:
		explicit data(const std::string& _type):type(_type){};
		virtual ~data() = default;

		virtual std::string what()
		{
			return type;
		};
		virtual void delete_this() = 0;
		virtual data* copy() = 0;
		virtual data* convert_type(std::string type) = 0;
	private:
		std::string type;
	};

	bool register_type(std::string name, construction_handle hd);
	void swap(data_container* da)
	{
		data* dt = d;
		this->d = da->d;
		da->d = dt;
	};
	void save(data* da)
	{
		if (d)delete d;
		d = da;
	};
	data* get() const
	{
		return d;
	};
	explicit operator data*() const{
		return d;
	};
private:
	data* d = nullptr;
	std::string type_;
	static std::map<std::string, construction_handle> construction_handles;
};

class database
{
public:
	database();
	virtual ~database();
	// Insert a element
	virtual void insert(const std::string& key, data_container* value);
	// Remove a element
	virtual void remove(const std::string& key);
	// Access a element
	virtual data_container* get(const std::string& key);
	// Access a element
	virtual data_container* operator[](const std::string& key)
	{
		return get(key);
	};
	// Get Whole data map
	virtual std::map<std::string, data_container*> get_data() {
		return data;
	};
	// Find if a key exists
	virtual bool contains(const std::string& key);

	static std::vector<std::string> SplitString(const std::string& s, const std::string& c);
protected:
	// Convert string to hex string
	static std::string str_to_hex(const std::string&, bool upper = false);
	// Convert hex string to string
	static std::string hex_to_str(const std::string&);
	std::map<std::string, data_container*> data;
};
#endif // DATABASE_H
