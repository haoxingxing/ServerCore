#include "log.h"
#include <iostream>
#include <typeinfo>

#include "ServerCore.h"
#ifdef _WIN32
#include <windows.h>
#endif
void log::print(log_level t, const std::string& info, bool i)
{
	if (t < verbose)
		return;
	std::string colorstr;
	std::string colorend = "\033[0m";
	if (!iscolored) {
		if (i)
			std::cout << info << std::endl;
		else
			std::cout << info;

		return;
	}
#ifndef _WIN32
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
#else
	switch (t)
	{
	case log::Debug:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case log::Info:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case log::Success:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case log::Warning:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case log::Error:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	}
	if (i)
		std::cout << info << std::endl;
	else
		std::cout << info;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
}

bool log::iscolored = true;
log::log_level log::verbose =
#ifndef DEBUG
Info;
#else
Debug;
#endif
#ifdef UsingMemoryLeakCheck
void MemoryLeak_Probe::MemoryLeakCheck()
{
	if (MemoryLeak_Probe::count != 0)
	{
		ERR("Memory Leaked:" + std::to_string(MemoryLeak_Probe::count));
		for (auto i =list.begin();i!=list.end();++i)
		{
			WARN("[" + std::string(typeid(**i).name()) + "] " + print_pointer(*i));
		}
		exit(EXIT_FAILURE);
	}
}

int MemoryLeak_Probe::count = 0;
std::list<MemoryLeak_Probe*> MemoryLeak_Probe::list = std::list<MemoryLeak_Probe*>();
#endif