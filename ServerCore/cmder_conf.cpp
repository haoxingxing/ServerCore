#include "cmder_conf.h"
#include "cmder.h"
#include <algorithm>
cmder_conf::cmder_conf()
{
}


void cmder_conf::str_to_map(const std::string& str)
{
	if (str.size() == 0)
	{
		ERR(TS_ID_1);
		return;
	}
	std::vector<std::string> v = SplitString(str, "\n");
	for (size_t i = 0; i < v.size(); ++i)
	{
		std::string m = v[i];
		if (m.find("#") != std::string::npos) {
			m = SplitString(m, "#")[0];
		}
		if (m.length() == 0)
		{
			continue;
		}
		commands.push_back(m);
		DEB("cmd " + m);
	}
}