//
// Created by panyuxuan on 2020/5/7.
//

#include "hashTable.h"

unsigned int hashTable::BKDRHash(char* key)
{
	unsigned int seed = 131;
	unsigned int hash = 0;

	while (*key != 0)
		hash = hash * seed + (*key++);

	return hash % MAX_DATA; // 10W data
}

hashTable::NODE* hashTable::create_node(size_t size)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	memset(node, 0, sizeof(NODE));

	node->data = (char*)malloc(size);
	memset(node->data, 0, size);
	node->next = nullptr;

	return node;
}

void hashTable::create_hash()
{
	flightName = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	customerId = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	customerName = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));

	memset(flightName, 0, sizeof(HASH_TABLE));
	memset(customerId, 0, sizeof(HASH_TABLE));
	memset(customerName, 0, sizeof(HASH_TABLE));

	flightName->head = create_node(FLIGHT_NAME_MAX_SIZE);
	customerId->head = create_node(CUSTOMER_ID_MAX_SIZE);
	customerName->head = create_node(CUSTOMER_NAME_MAX_SIZE);

	flightName->chain = (NODE**)malloc(MAX_DATA * sizeof(NODE*));
	customerId->chain = (NODE**)malloc(MAX_DATA * sizeof(NODE*));
	customerName->chain = (NODE**)malloc(MAX_DATA * sizeof(NODE*));

	for (int i = 0; i < MAX_DATA; i++)
	{
		flightName->chain[i] = (NODE*)malloc(sizeof(NODE));
		customerId->chain[i] = (NODE*)malloc(sizeof(NODE));
		customerName->chain[i] = (NODE*)malloc(sizeof(NODE));

		memset(flightName->chain[i], 0, sizeof(NODE));
		memset(customerId->chain[i], 0, sizeof(NODE));
		memset(customerName->chain[i], 0, sizeof(NODE));
	}
}

void hashTable::destroy_hash()
{
	for (int i = 0; i < MAX_DATA; i++)
	{
		free(flightName->chain[i]);
		free(customerId->chain[i]);
		free(customerName->chain[i]);
	}

	free(flightName->head);
	free(customerId->head);
	free(customerName->head);

	free(flightName->chain);
	free(customerId->chain);
	free(customerName->chain);
}

hashTable::hashTable()
{
	create_hash();
}

hashTable::~hashTable()
{
	destroy_hash();
}
