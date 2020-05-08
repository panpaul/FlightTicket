//
// Created by panyuxuan on 2020/5/7.
//

#include "service/customer.h"
#include "database/hashTable.h"
#include <cstdio>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	auto* name = (char*)"中文English";
	auto* id = (char*)"123456789012345678";
	auto c = new customer(name);
	c->new_customer(id);
	c->query();
	delete c;

	auto hash = new hashTable();
	char str[10];
	for (int i = 1; i <= 100; i++)
	{
		sprintf(str, "%d", i);
		hash->insert_customer_id(str);
	}
	char find[10] = "5";
	printf("%s\n", hash->find_customer_id(find)->data);

	delete hash;

	return 0;
}