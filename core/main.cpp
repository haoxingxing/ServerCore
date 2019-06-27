#include "log.h"
#include "file.h"
#include "function.h"
#include "repo_version.h"
#include "ast.h"
#include <iostream>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
void Dump(const ast::tree& t)
{
	std::cout << "\"" << t.data << "\" : {\n";//"type:" << t.type << ",\n";
	for (const auto& x : t.args)
	{
		Dump(x);
	}
	std::cout << "},\n";
}
void Run(const std::string& _file)
{
	srand(time(nullptr));
	auto time = clock();
	file f(_file);
	auto x = ast::split(f.read());
	auto n = ast::analysis(x);
	cout << "File " << _file << " Parsed in " << 1000.0 * (double(clock()) - time) / CLOCKS_PER_SEC << " ms" << endl;
	//Dump(n);
	time = clock();{
		_function t;
		t.new_this();
		t.run(n);
	}
	cout << "\nFile " << _file << " Finished in " << 1.000 * (double(clock()) - time) / CLOCKS_PER_SEC << " s" << endl;
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