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
void dump(ast::tree* v);
void Run(const std::string& _file)
{
	srand(time(nullptr));
	auto time = clock();
	file f(_file);
	auto x = ast::split(f.read());
	auto n = ast::analysis(x);
	dump(n);
	cout << "\nFile " << _file << " Parsed in " << 1000.0 * (double(clock()) - time) / CLOCKS_PER_SEC << " ms" << endl;
	time = clock(); {
		_function t;
		t.new_this();
		delete t.process(n, t.member);
	}
	cout << "\nFile " << _file << " Finished in " << 1.000 * (double(clock()) - time) / CLOCKS_PER_SEC << " s" << endl;
}

void dump(ast::tree* v)
{
	if (v == nullptr)
		return;
	cout << "{";
	cout << "\"left\":";
	dump(v->left);
	cout << ",\"" << v->key << '"' << ":[";
	for (auto n : v->args)
		dump(n);
	cout << "],";
	cout << "\"operation\":" << v->operation << " ,";
	cout << "\"right\":";
	dump(v->right);
	cout << "},";
}

int main(int argc, char** argv)
{
	//	std::string n = "cout(\"Hello World!\".append(\"StarCore\")).plus(1)";
	//	cout << n << endl;
	//	auto tmp = ast::find_method(n);
	//	cout << n << endl;
	//	dump(tmp);
	//	n = "builtin.cout(\"Hello World!\",\"2333\").plus(233).haha()";
	//	cout << endl << stropr::dig(n) << endl << n << endl;
	//while (true)
	//{
	//	std::vector<std::string> n;
	//	n.emplace_back();
	//	for (size_t i = 0;; i++) {
	//		getline(cin, n[i]);
	//		if (n[i] == "END") {
	//			n.erase(n.end() - 1);
	//			break;
	//		}
	//		n.emplace_back();
	//	}
	//	auto handle = ast::analysis(n);
	//	dump(handle);
	//	delete handle;
	//	cout << endl;
	//}
	//auto x = stropr::SeparateStringPrioritized("\"23 = 3\"t=\"23=3\"");
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