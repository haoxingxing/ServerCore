#include "ServerCore.h"
#include "log.h"
#include "file.h"
#include "database.h"
#include "configmgr.h"
#include "cmder.h"
#include <iostream>
using namespace std;

int main()
{
	cmder t(true, "test.conf");
	t.run();
	return 0;
}

hash_t hash_(char const* str)
{
	hash_t ret{ basis };

	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}