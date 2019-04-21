#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "database.h"
#include "cmder_conf.h"
#include "cmder.h"
#include <iostream>
using namespace std;

int main()
{
	{
		file f("test.conf");
		cmder t;
		t.str_to_map(f.read());
		t.run();
	}
	MemoryLeak_Probe::MemoryLeakCheck();
	return 0;
}