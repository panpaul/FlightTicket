//
// Created by panyuxuan on 2020/5/7.
//

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <cstdlib>
#include <cstring>

class hashTable
{
 private:
	typedef struct NODE
	{
		char* data{};
		struct NODE* next{};
	} node;

	typedef struct HASH_TABLE
	{
		NODE* head;
		NODE** chain;
	} hash_table;

	static unsigned int BKDRHash(char* key);
	NODE* create_node();
};

#endif //_HASHTABLE_H_
