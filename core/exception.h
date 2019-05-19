#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
#include <vector>
#include <exception>
class except : public std::exception
{
public:
	except(const std::string& reason,const std::string& this_where);
	void add_where(const std::string& this_where);
	std::vector<std::string> s() const;
	std::string _what() const;
private:
	std::string w;
	std::vector<std::string> where;	
};

#define NEW_EXCEPT(reason) except(reason,__FUNCTION__)
#define ADD_EXCEPT(exp) exp.add_where(__FUNCTION__)
#endif // EXCEPTION_H
