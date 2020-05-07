//
// Created by panyuxuan on 2020/5/7.
//

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "../definitions.h"
#include <cstdlib>
#include <cstring>

/*
 * 对于数据库需要索引的是航班号和客户的姓名
 * 对于航班号而言,一般是CA1234之类的char*,需要维护一个hashtable(char* -> int/long)
 * 对于客户而言,存在重名现象,所以以ID(char* 为什么身份证有"X"!!)为索引,需要维护一个hashtable(char* -> int/long)然后维护姓名<->ID的关系

 */
class hashTable
{
 private:
	typedef struct
	{
		char* data{};
		struct NODE* next{};
	} NODE;

	typedef struct
	{
		NODE* head;
		NODE** chain;
	} HASH_TABLE;

	/*
	 * flightName: name->int/long
	 * customerId: id->int/long
	 * customerName: name->int/long(hashed id)
	 */
	HASH_TABLE* flightName{}, * customerId{}, * customerName{};

	static unsigned int BKDRHash(char* key);
	static NODE* create_node(size_t size);
	void create_hash();
	void destroy_hash();

 public:
	hashTable();
	~hashTable();
};

#endif //_HASHTABLE_H_
