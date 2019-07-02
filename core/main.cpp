#include "log.h"
#include "file.h"
#include "function.h"
#include "repo_version.h"
#include "ast.h"
#include <iostream>
#include <ctime>
#include "tools.h"
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
//void Run(const std::string& _file)
//{
//	srand(time(nullptr));
//	auto time = clock();
//	file f(_file);
//	auto x = ast::split(f.read());
//	auto n = ast::analysis(x);
//	cout << "File " << _file << " Parsed in " << 1000.0 * (double(clock()) - time) / CLOCKS_PER_SEC << " ms" << endl;
//	//Dump(n);
//	time = clock();{
//		_function t;
//		t.new_this();
//		t.run(n);
//	}
//	cout << "\nFile " << _file << " Finished in " << 1.000 * (double(clock()) - time) / CLOCKS_PER_SEC << " s" << endl;
//}

void dump(ast::tree* v)
{
	if (v == nullptr)
		return;
	cout << "{";
	cout << "\"left\":";
	dump(v->left);
	cout << "\"" << v->key << '"' << ":{";
	for (auto n : v->args)
		dump(n);
	cout << "\"operation\":" << v->operation << " ,";
	cout << "},";
	cout << "\"right\":";
	dump(v->right);
	cout << "},";
}

int main(int argc, char** argv)
{
	std::string n = "builtin.cout(\"Hello World!\",\"2333\").plus(233).haha()";
	auto tmp = ast::find_method(n);
	dump(tmp);
	//n = "builtin.cout(\"Hello World!\",\"2333\").plus(233).haha()";
	//cout << endl << stropr::dig(n) << endl << n << endl;
	//while (true)
	//{
	//	cin >> n;
	//	dump(ast::find_method(n));
	//}

	//auto x = stropr::SeparateStringPrioritized("\"23 = 3\"t=\"23=3\"");
	//#ifdef _WIN32
	//	system("chcp 65001");
	//#endif
	//#ifdef DEBUG
	//	log::print(log::Info, "StarCore " REPO_VERSION);
	//#endif
	//	if (argc == 1)
	//	{
	//#ifndef DEBUG
	//		log::print(log::Info, "StarCore " REPO_VERSION);
	//#endif
	//	}
	//	else if (argc > 1)
	//	{
	//		//Run(string(argv[1]));
	//	}
	//#ifdef UsingMemoryLeakCheck
	//	MemoryLeak_Probe::MemoryLeakCheck();
	//#endif
	return 0;
}