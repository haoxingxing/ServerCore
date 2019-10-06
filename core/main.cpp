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
void RunFile(const std::string& _file)
{
	auto start_time = clock();
	file f(_file);
	auto x = ast::split(f.read());
	auto n = ast::analysis(x);
	auto end_time = clock();
	dump(n);
	cout << "\nFile " << _file << " Parsed in " << 1000.0 * (double(end_time) - start_time) / CLOCKS_PER_SEC << " ms" << endl;
	start_time = clock();
	{
		_function t;
		t.new_this();
		delete t.process(n, t.member);
	}
	delete n;
	cout << "\nFile " << _file << " Finished in " << 1.000 * (double(clock()) - start_time) / CLOCKS_PER_SEC << " s" << endl;
}

void cmdRun() {
	cout << "Cmdline Input {" << endl;
	string cmds;
	int line = 1,tabs = 1;
	while (true) {
		cout <<  line++;
		for (int i = 0; i < tabs; i++)
			cout << "	";
		string tmp;
		getline(cin, tmp);
		if (tmp.find('}') == cmds.npos) {
			cmds.append(tmp);
			if (tmp=="end" || tmp == "end;")
				tabs--;
			if (tmp.find("if(") != tmp.npos)
				tabs++;
			if (tmp.find("while(") != tmp.npos)
				tabs++;

		}
		else
		{
			cmds.append(tmp.substr(0, tmp.find('}'))+";");
			break;
		}
	}
	auto x = ast::split(cmds);
	auto n = ast::analysis(x);
	dump(n);
	cout << endl;
	auto start_time = clock();
	{
		_function t;
		t.new_this();
		delete t.process(n, t.member);
	}
	delete n;
	cout << "\n Finished in " << 1.000 * (double(clock()) - start_time) / CLOCKS_PER_SEC << " s" << endl;

	
}

void dump(ast::tree* v)
{
	if (v == nullptr) {
		cout << "null";
		return;
	}
	cout << "{";
	cout << "\"left\":";
	dump(v->left);
	cout << R"(,"key":")" << stropr::ReplaceAll(v->key, "\"", "\\\"") << R"(","body")" << ":[";
	for (size_t i = 0; i < v->args.size(); i++) {
		dump(v->args[i]);
		if (i != v->args.size() - 1)
			cout << ",";
	}
	cout << "],";
	cout << "\"operation\":" << v->operation << " ,";
	cout << "\"right\":";
	dump(v->right);
	cout << "}";
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
		cmdRun();
#endif
	}
	else if (argc > 1)
	{
		RunFile(string(argv[1]));
	}
#ifdef UsingMemoryLeakCheck
	MemoryLeak_Probe::MemoryLeakCheck();
	if (ast::tree::counter!=0)
		WARN("tree memory leaked:"+std::to_string(ast::tree::counter));
#endif
	return 0;
}