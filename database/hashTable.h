//
// Created by panyuxuan on 2020/5/7.
//

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "../definitions.h"
#include <cstddef>
#include <cstring>
#include <fstream>

/*
 * 对于数据库需要索引的是航班号和客户的姓名
 * 对于航班号而言,一般是CA1234之类的char*,需要维护一个hashtable(char* -> int/long)
 * 对于客户而言,存在重名现象,所以以ID(char* 为什么身份证有"X"!!)为索引,需要维护一个hashtable(char* -> int/long)然后维护姓名<->ID的关系

 */
class hashTable
{
 private:
	typedef struct NODE
	{
		char* data{};
		NODE* next{};
	} NODE;

	typedef struct HASH_TABLE
	{
		size_t size;
		NODE* head; // 临时存放节点,方便内存管理
		NODE** chain;
	} HASH_TABLE;

	/*
	 * flightName: name->int/long
	 * customerId: id->int/long
	 * customerName: name->int/long(hashed id)
	 */
	HASH_TABLE* flightName{}, * customerId{}, * customerName{};

	static unsigned int BKDRHash(const char* key);

	static NODE* create_node(size_t size);
	void create_hash();

	void destroy_node(NODE* node);
	void destroy_hash(HASH_TABLE* hashTable);

	void save(HASH_TABLE* hashTable, const std::string& file);
	void read(HASH_TABLE* hashTable, const std::string& file);

	bool insert(HASH_TABLE* hashTable, const char* data);
 public:
	hashTable();
	~hashTable();
	// TODO combine them
	NODE* find_flight_name(char* data);
	NODE* find_customer_id(char* data);
	NODE* find_customer_name(char* data);

	bool insert_flight_name(char* data);
	bool insert_customer_id(char* data);
	bool insert_customer_name(char* data);

	bool delete_flight_name(char* data);
	bool delete_customer_id(char* data);
	bool delete_customer_name(char* data);

};

#endif //_HASHTABLE_H_
