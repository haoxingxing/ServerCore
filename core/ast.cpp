#include "ast.h"
#include "domain.h"
std::vector<std::string> ast::split(const std::string& raw)
{
	/*
	 * var(x,"");
	 * x;
	 * var(first,x.at(1));
	 * if(first.equals(23));
	 * echo("Equals");
	 * else;
	 * echo("Not Equals");
	 * end;
	 * while(first.less(128));
	 * echo(first);
	 * var(first,first.minus(1));
	 * end;
	 */
	std::vector<std::string> r;
	auto RawSplit=domain::SplitString(raw,";");
	r.reserve(RawSplit.size());
	for(const auto& branch : RawSplit)
	{
		//TODO: Auto Clean the code
		r.push_back(branch);
	}
	return r;
}
