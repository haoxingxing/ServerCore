#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <iomanip>
#include "ServerCore.h"
#include "log.h"
#include "file.h"
class data_container;
class data
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data(const std::string & _type = "void") :type(_type) {
		DEB(print_pointer(this));
	};
	virtual ~data() {
		DEB(print_pointer(this));
	};
	virtual std::string what() { return type; };
	virtual void delete_this() { delete this; };
	virtual data_container& convert_type(const std::string&);;
	virtual bool is_convertible_to(const std::string&) { return false; };
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
private:
	std::string type;
};
class data_void;
class data_container
{
public:
	explicit data_container(const std::string& type = "void", data* d = nullptr);;
	~data_container() {
		DEB(print_pointer(this));
		if (d != nullptr)
			d->delete_this();
		d = nullptr;
	};
	std::string what() const { return type_; };
	void swap(data_container * s)
	{
		if (this->type_ != s->type_)
		{
			this->swap(&(s->get()->convert_type(type_)));
		}
		else
		{
			data* dt = d;
			this->d = s->d;
			s->d = dt;
		}
	}
	void save(data * da)
	{
		if (d != nullptr) delete d;
		if (da->what() == type_)d = da;
	};
	data_container * copy() const
	{
		return new data_container(type_, d);
	};
	data* get() const { return d; };
	explicit operator data* () const { return d; };
private:
	data* d = nullptr;
	std::string type_;
};

class database
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	database();
	virtual ~database();
	// Insert a element
	virtual void insert(const std::string & key, data_container * value);
	// Remove a element
	virtual void remove(const std::string & key);
	// Access a element
	virtual data_container* get(const std::string & key);
	// Access a element
	virtual data_container* operator[](const std::string & key)
	{
		return get(key);
	};
	// Get Whole data map
	virtual std::map<std::string, data_container*> get_data() {
		return _data;
	};
	// Find if a key exists
	virtual bool contains(const std::string & key) {
		return _data.find(key) != _data.end();
	};

	static std::vector<std::string> SplitString(const std::string & s, const std::string & c);
protected:
	// Convert string to hex string
	static std::string str_to_hex(const std::string&, bool upper = false);
	// Convert hex string to string
	static std::string hex_to_str(const std::string&);
	std::map<std::string, data_container*> _data;
};

#endif // DATABASE_H
