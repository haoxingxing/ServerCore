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
	cmder t;	
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