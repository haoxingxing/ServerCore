#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "database.h"
#include "configmgr.h"
#include <iostream>
using namespace std;

int main()
{
	ConfigMgr t("test");
	t.loadfromfile();
	t.writetofile();
	return 0;
}