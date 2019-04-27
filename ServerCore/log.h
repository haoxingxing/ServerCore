#ifndef COLOR_PRInt_H
#define COLOR_PRInt_H
#include <string>
#define UsingMemoryLeakCheck
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
	static void print(log_level, const std::string& info, bool t = true);
	static bool iscolored;
};
#ifdef UsingMemoryLeakCheck
class MemoryLeak_Probe
{
public:
	MemoryLeak_Probe()
	{
		count++;
	};
	virtual ~MemoryLeak_Probe()
	{
		count--;
	}
	static void MemoryLeakCheck() {
		if (MemoryLeak_Probe::count != 0)
			log::print(log::Error, "Memory Leaked:" + std::to_string(MemoryLeak_Probe::count));
	}
	static int count;
};

#endif

#endif
