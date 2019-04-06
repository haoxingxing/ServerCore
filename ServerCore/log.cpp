#include "log.h"

void log::print(log_level t,const std::string& info,bool i)
{
	std::string colorstr;
	std::string colorend = "\033[0m";
	if (!iscolored) {
		if (i)
			std::cout << info << std::endl;
		else
			std::cout << info;

		return;
	}
	switch (t)
	{
	case log::Debug:
		colorstr = "\033[0m";
		break;
	case log::Info:
		colorstr = "\033[1m";
		break;
	case log::Success:
		colorstr = "\033[32;1m";
		break;
	case log::Warning:
		colorstr = "\033[33;1m";
		break;
	case log::Error:
		colorstr = "\033[31;1m";
		break;
	}	
	if (i)
		std::cout << colorstr << info << colorend << std::endl;
	else
		std::cout << colorstr << info << colorend;
}

bool log::iscolored = true;
