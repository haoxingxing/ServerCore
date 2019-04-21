#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <iomanip>
#include "ServerCore.h"
#include "log.h"
#include "file.h"
class data
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data(const std::string& _type) :type(_type) {
		DEB(print_pointer(this));
	};
	virtual ~data(){
		DEB(print_pointer(this));
	};
	virtual std::string what() { return type; };
	virtual void delete_this() { delete this; };
	virtual data* convert_type(const std::string&) { return nullptr; };
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
private:
	std::string type;
};

class data_container
{
public:
	explicit data_container(const std::string& type = "void",data* d = nullptr):d(d),type_(type){
		DEB(print_pointer(this));
	};
	~data_container(){
		DEB(print_pointer(this));
		if (d != nullptr)
			d->delete_this();
		d = nullptr;		
	};
	std::string what() const { return type_; };
	void swap(data_container* s)
	{
		if (this->type_!=s->type_)
		{
			ERR(TS_ID_29);
		}
		else
		{
			data* dt = d;
			this->d = s->d;
			s->d = dt;
		}
	}
	void save(data* da)
	{	
		if (d!=nullptr)delete d;
		if (da->what() == type_){d = da;}else{d = da->convert_type(type_);}
	};
	data_container* copy() const
	{
		return new data_container(type_, d);
	};
	data* get() const {	return d;};
	explicit operator data*() const{return d;};
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
		return _data;
	};
	// Find if a key exists
	virtual bool contains(const std::string& key) {
		return _data.find(key) != _data.end();
	};

	static std::vector<std::string> SplitString(const std::string& s, const std::string& c);
protected:
	// Convert string to hex string
	static std::string str_to_hex(const std::string&, bool upper = false);
	// Convert hex string to string
	static std::string hex_to_str(const std::string&);
	std::map<std::string, data_container*> _data;
};

class data_int : public data
{
public:
	data_int(const int& a = 0) :data("int") { d = a; }
	int& access() { return  d; }
private:
	int d;
};

class data_string : public data
{
public:
	data_string(const std::string& a = 0) :data("string") { d = a; }
	std::string& access() { return  d; }
private:
	std::string d;
};

#endif // DATABASE_H
