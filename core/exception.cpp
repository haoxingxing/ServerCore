#include "exception.h"
except::except(const std::string& reason,const std::string& this_where) : exception(reason.c_str())
{
	where.emplace_back(this_where);	
}
void except::add_where(const std::string& this_where)
{
	where.push_back(this_where);
}
std::vector<std::string> except::s() const
{
	return where;
}
