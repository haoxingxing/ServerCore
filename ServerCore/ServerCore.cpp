#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "cmder_conf.h"
#include "cmder.h"
#include "repo_version.h"
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;

void Run(const std::string& _file)
{
	file f(_file);
	cmder  t;
	t.str_to_map(f.read());
	t.run();
}

int main(int argc, char** argv)
{
#ifdef _WIN32
	system("chcp 65001");
#endif
#ifdef DEBUG
	log::print(log::Info, "StarCore " REPO_VERSION);
#endif
	if (argc == 1)
	{
#ifndef DEBUG
		log::print(log::Info, "StarCore " REPO_VERSION);
#endif
	}
	else if (argc > 1)
	{
		Run(string(argv[1]));
	}
#ifdef UsingMemoryLeakCheck
	MemoryLeak_Probe::MemoryLeakCheck();
#endif
	return 0;
}