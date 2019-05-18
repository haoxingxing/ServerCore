#include "log.h"
#include "file.h"
#include "function.h"
#include "repo_version.h"
#include "ast.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
void Dump(ast::tree t)
{
	std::cout << "\"" << t.data << "\" : {\n";
	for (auto x : t.args)
	{
		Dump(x);
	}
	std::cout << "},\n";
}
void Run(const std::string& _file)
{
	file f(_file);
	auto x = ast::split(f.read());
	auto n = ast::analysis(x);
	Dump(n);
	//function t;
	//t.new_this();
	//t.ProcessDefine(f.read());
	//t.run();
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