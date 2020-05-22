//
// Created by panyuxuan on 2020/5/7.
//

#include "service/customer.h"
#include "database/hashTable.h"
#include "database/linearEngine.h"
#include <cstdio>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	auto* name = (char*)"中文English";
	auto* id = (char*)"123456789012345678";
	auto c = new customer(name);
	c->new_customer(id);
	c->query();
	delete c;

	auto hash = new db::hashTable();
	char str[30];
	for (int i = 1; i <= MAX_DATA - 1; i++)
	{
		//hash->insert_customer_id(str);
	}

	printf("%s\n", hash->find_customer_id("QA0FVdUTmIidAoQ4wrGm")->data);

	delete hash;

	auto le = new db::linearEngine(".");
	delete le;

	return 0;
}