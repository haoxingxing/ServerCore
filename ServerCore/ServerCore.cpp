// ServerCore.cpp: 定义应用程序的入口点。
//

#include "ServerCore.h"
#include "log.h"
using namespace std;

int main()
{
	
	log::print(log::NONE, "H",false);
	log::print(log::NOTICE, "e",false);
	log::print(log::WARN, "ll",false);
	log::print(log::ERR, "o");
	log::print(log::ERR, "W",false);
	log::print(log::WARN, "o",false);
	log::print(log::NOTICE, "r",false);
	log::print(log::NONE, "ld");
	return 0;
}
