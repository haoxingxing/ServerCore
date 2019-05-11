#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <iomanip>
#include <memory>
#include "core.h"
#include "log.h"
class data_container;
class database;
class data
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data(std::string type = "void",const data * parent = nullptr);
	virtual ~data();
	virtual std::string what() { return type; };
	virtual data* make_copy() = 0;
	virtual data_container* access_member(const std::string& name);
	virtual void delete_this() { delete this; };
	virtual data_container* execute(const std::vector<data_container*>&) { return nullptr; };
	virtual std::shared_ptr<data_container> convert_type(const std::string&);
	template<typename T>
	T* to() { return dynamic_cast<T*>(this); };
	database* member;
private:
	bool is_member_own;
	std::string type;
};
class data_void;
class data_container
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	explicit data_container(data * *d) : d(d), iscopy(true)
	{
		DEB(PRINT_POINTER(this));
	};
	explicit data_container(data* d = nullptr);;
	~data_container() {
		DEB(PRINT_POINTER(this));
		if (!iscopy)
		{
			if ((*d) != nullptr)
				(*d)->delete_this();
			*d = nullptr;
			delete d;
		}
	};
	void copy_value(data_container * s) const { if ((*d) != nullptr)(*d)->delete_this(); *d = nullptr; *(this->d) = (*(s->d))->make_copy(); }
	[[nodiscard]] data_container* copy() const { return new data_container(d); };
	[[nodiscard]] data* get() const { return *d; };
	explicit operator data* () const { return *d; };
private:
	data** d = nullptr;
	bool iscopy;
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
	std::map<std::string, data_container*> _data;
};

#endif // DATABASE_H
