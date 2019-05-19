#include "exception.h"
except::except(const std::string& reason,const std::string& this_where)
{
	where.emplace_back(this_where);
	w=reason;
}
void except::add_where(const std::string& this_where)
{
	where.push_back(this_where);
}
std::vector<std::string> except::s() const
{
	return where;
}
std::string except::_what() const
{
	return w;
}
