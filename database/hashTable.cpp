//
// Created by panyuxuan on 2020/5/7.
//

#include "hashTable.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

unsigned int hashTable::BKDRHash(char* key)
{
	unsigned int seed = 131;
	unsigned int hash = 0;

	while (*key != 0)
		hash = hash * seed + (*key++);

	return hash % MAX_DATA;
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

void hashTable::destroy_node(NODE* node)
{
	if (node == nullptr)return;

	free(node->data);
	destroy_node(node->next);

	free(node);
}

void hashTable::destroy_hash(HASH_TABLE* hashTable)
{
	if (hashTable == nullptr)return;

	destroy_node(hashTable->head);

	for (int i = 0; i < MAX_DATA; i++)
	{
		destroy_node(hashTable->chain[i]);
	}

	free(hashTable->chain);

	free(hashTable);
}

hashTable::hashTable()
{
	std::ifstream ifs("hashTable.data");
	if (!ifs.is_open())
	{
		// file not exist or failed to open
		std::cerr << "Failed to open hashTable.data" << std::endl;
		create_hash();
	}
	else
	{
		//load data
		// TODO replace it
		create_hash();
	}
	ifs.close();
}

hashTable::~hashTable()
{
	std::ofstream ofs("hashTable.data", std::ios_base::out | std::ios_base::trunc);
	if (!ofs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open hashTable.data" << std::endl;
	}
	else
	{
		//dump data
	}
	ofs.close();
	destroy_hash(flightName);
	destroy_hash(customerId);
	destroy_hash(customerName);
}

hashTable::NODE* hashTable::find_flight_name(char* data)
{
	if (flightName == nullptr)
	{
		return nullptr;
	}
	NODE* head = flightName->chain[BKDRHash(data)];
	while (head != nullptr)
	{
		if (strncmp(head->data, data, FLIGHT_NAME_MAX_SIZE / sizeof(char)) == 0)
			return head;
		else
			head = head->next;
	}
	return nullptr;
}

hashTable::NODE* hashTable::find_customer_id(char* data)
{
	if (customerId == nullptr)
	{
		return nullptr;
	}
	NODE* head = customerId->chain[BKDRHash(data)];
	while (head != nullptr)
	{
		if (strncmp(head->data, data, CUSTOMER_ID_MAX_SIZE / sizeof(char)) == 0)
			return head;
		else
			head = head->next;
	}
	return nullptr;
}

hashTable::NODE* hashTable::find_customer_name(char* data)
{
	if (customerName == nullptr)
	{
		return nullptr;
	}
	NODE* head = customerName->chain[BKDRHash(data)];
	while (head != nullptr)
	{
		if (strncmp(head->data, data, CUSTOMER_NAME_MAX_SIZE / sizeof(char)) == 0)
			return head;
		else
			head = head->next;
	}
	return nullptr;
}

bool hashTable::insert_flight_name(char* data)
{
	if (flightName == nullptr)
		return false;

	if (flightName->chain[BKDRHash(data)]->data == nullptr)
	{
		NODE* node = create_node(FLIGHT_NAME_MAX_SIZE);

		strcpy(node->data, data);
		node->next = nullptr;
		flightName->chain[BKDRHash(data)]->data = node->data;
		flightName->chain[BKDRHash(data)]->next = node->next;

		free(node);
		return true;
	}
	else
	{
		flightName->head = flightName->chain[BKDRHash(data)];
		while (flightName->head->next != nullptr)
			flightName->head = flightName->head->next;
		flightName->head->next = create_node(FLIGHT_NAME_MAX_SIZE);

		strcpy(flightName->head->next->data, data);
		flightName->head->next->next = nullptr;

		return true;
	}
}

bool hashTable::insert_customer_id(char* data)
{
	if (customerId == nullptr)
		return false;

	if (customerId->chain[BKDRHash(data)]->data == nullptr)
	{
		NODE* node = create_node(CUSTOMER_ID_MAX_SIZE);

		strcpy(node->data, data);
		node->next = nullptr;
		customerId->chain[BKDRHash(data)]->data = node->data;
		customerId->chain[BKDRHash(data)]->next = node->next;

		free(node);
		return true;
	}
	else
	{
		customerId->head = customerId->chain[BKDRHash(data)];
		while (customerId->head->next != nullptr)
			customerId->head = customerId->head->next;
		customerId->head->next = create_node(CUSTOMER_ID_MAX_SIZE);

		strcpy(customerId->head->next->data, data);
		customerId->head->next->next = nullptr;

		return true;
	}
}

bool hashTable::insert_customer_name(char* data)
{
	if (customerName == nullptr)
		return false;

	if (customerName->chain[BKDRHash(data)]->data == nullptr)
	{
		NODE* node = create_node(CUSTOMER_NAME_MAX_SIZE);

		strcpy(node->data, data);
		node->next = nullptr;
		customerName->chain[BKDRHash(data)]->data = node->data;
		customerName->chain[BKDRHash(data)]->next = node->next;

		free(node);
		return true;
	}
	else
	{
		customerName->head = customerName->chain[BKDRHash(data)];
		while (customerName->head->next != nullptr)
			customerName->head = customerName->head->next;
		customerName->head->next = create_node(CUSTOMER_NAME_MAX_SIZE);

		strcpy(customerName->head->next->data, data);
		customerName->head->next->next = nullptr;

		return true;
	}
}

bool hashTable::delete_flight_name(char* data)
{
	flightName->head->next = create_node(FLIGHT_NAME_MAX_SIZE);
	flightName->head->next = flightName->chain[BKDRHash(data)];

	if (flightName == nullptr)
		return false;

	while (flightName->head->next != nullptr)
	{
		if (strncmp(flightName->head->next->data, data, FLIGHT_NAME_MAX_SIZE / sizeof(char)) == 0)
		{

			if (flightName->head->next->data == flightName->chain[BKDRHash(data)]->data)
				flightName->chain[BKDRHash(data)] = flightName->head->next->next;
			else
				flightName->head->next = flightName->head->next->next;
			return true;
		}
		else
			flightName->head->next = flightName->head->next->next;
	}

	free(flightName->head->next);

	return false;
}

bool hashTable::delete_customer_id(char* data)
{
	customerId->head->next = create_node(CUSTOMER_ID_MAX_SIZE);
	customerId->head->next = customerId->chain[BKDRHash(data)];

	if (customerId == nullptr)
		return false;

	while (customerId->head->next != nullptr)
	{
		if (strncmp(customerId->head->next->data, data, CUSTOMER_ID_MAX_SIZE / sizeof(char)) == 0)
		{

			if (customerId->head->next->data == customerId->chain[BKDRHash(data)]->data)
				customerId->chain[BKDRHash(data)] = customerId->head->next->next;
			else
				customerId->head->next = customerId->head->next->next;
			return true;
		}
		else
			customerId->head->next = customerId->head->next->next;
	}

	free(customerId->head->next);

	return false;
}

bool hashTable::delete_customer_name(char* data)
{
	customerName->head->next = create_node(CUSTOMER_NAME_MAX_SIZE);
	customerName->head->next = customerName->chain[BKDRHash(data)];

	if (customerName == nullptr)
		return false;

	while (customerName->head->next != nullptr)
	{
		if (strncmp(customerName->head->next->data, data, CUSTOMER_NAME_MAX_SIZE / sizeof(char)) == 0)
		{

			if (customerName->head->next->data == customerName->chain[BKDRHash(data)]->data)
				customerName->chain[BKDRHash(data)] = customerName->head->next->next;
			else
				customerName->head->next = customerName->head->next->next;
			return true;
		}
		else
			customerName->head->next = customerName->head->next->next;
	}

	free(customerName->head->next);

	return false;
}
