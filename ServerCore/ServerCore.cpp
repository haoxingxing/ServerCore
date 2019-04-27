﻿#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "database.h"
#include "cmder_conf.h"
#include "cmder.h"
#include "repo_version.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;

void Run(std::string _file)
{
	file f(_file);
	cmder t;
	t.str_to_map(f.read());
	t.run();
}

int main(int argc, char** argv)
{
#ifdef _WIN32
	system("chcp 65001");
#endif
	if (argc == 1)
	{
		log::print(log::Info, "ServerCore " REPO_VERSION "+" REPO_HASH);
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