#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <iomanip>
#include <memory>
#include "ServerCore.h"
#include "log.h"
#include "file.h"
#define Type(ptr) (ptr==nullptr)?"null":ptr->what()
class data_container;
class database;
class data
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data(const std::string & _type = "void",const data * parent = nullptr);
	virtual ~data();;
	virtual std::string what() { return type; };
	virtual data_container* access_member(const std::string& name);
	virtual void delete_this() { delete this; };
	virtual data_container* execute(std::vector<data_container*>) { return nullptr; };
	virtual std::shared_ptr<data_container> convert_type(const std::string&);
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
	database* member;
private:
	std::string type;
};
class data_void;
class data_container
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data_container(std::shared_ptr<data> d) : d(d)
	{
		DEB(print_pointer(this));
	}
	explicit data_container(data* d = nullptr) : d(std::shared_ptr<data> (d))
	{
		DEB(print_pointer(this));
	}
	~data_container() {
		DEB(print_pointer(this));
		d.reset();	
	};
	void swap(data_container * s)
	{	
		d.reset();
		this->d = s->d;
	}
	data* get() const { return d.get(); };
	explicit operator data* () const { return d.get(); };
private:
	std::shared_ptr<data> d = nullptr;
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
