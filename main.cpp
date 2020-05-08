//
// Created by panyuxuan on 2020/5/7.
//

#include "service/customer.h"
#include "database/hashTable.h"

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
	delete hash;

	return 0;
}