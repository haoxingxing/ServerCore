#ifndef COLOR_PRInt_H
#define COLOR_PRInt_H
#include <string>
#include "global.h"
#include <list>
class log {
public:
	static enum log_level
	{
		Debug,
		Info,
		Success,
		Warning,
		Error
	}verbose;
	/*
	Print logs with level
	Debug
	Info
	Success
	Warning
	Error
	*/
	static void print(log_level, const std::string& info, bool i = true);
	static bool iscolored;
};
#ifdef UsingMemoryLeakCheck
class MemoryLeak_Probe
{
public:
	MemoryLeak_Probe()
	{
		list.push_back(this);
		count++;
	};
	virtual ~MemoryLeak_Probe()
	{
		list.remove(this);
		count--;
	}
	static void MemoryLeakCheck();
	static int count;
	static std::list<MemoryLeak_Probe*> list;
};

#endif

#endif
