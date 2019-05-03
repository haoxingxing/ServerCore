#include "cmder_conf.h"
#include "cmder.h"
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
	for (auto m : v)
	{
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