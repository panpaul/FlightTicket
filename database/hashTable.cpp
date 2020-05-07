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

	return hash % 100000; // 10W data
}

hashTable::NODE* hashTable::create_node()
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	memset(node, 0, sizeof(NODE));

	node->data = (char*)malloc(STRLEN * sizeof(char));
	memset(node->data, 0, STRLEN * sizeof(char));
	node->next = nullptr;

	return node;
}

