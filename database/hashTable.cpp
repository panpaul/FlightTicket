//
// Created by panyuxuan on 2020/5/7.
//

#include "hashTable.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

unsigned int hashTable::BKDRHash(const char* key)
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

	flightName->size = FLIGHT_NAME_MAX_SIZE;
	customerId->size = CUSTOMER_ID_MAX_SIZE;
	customerName->size = CUSTOMER_NAME_MAX_SIZE;

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

void hashTable::save(hashTable::HASH_TABLE* hashTable, const std::string& file)
{
	std::ofstream ofs(file, std::ios_base::out | std::ios_base::trunc);
	if (!ofs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << file << std::endl;
	}
	else
	{
		//dump data
		for (int i = 0; i < MAX_DATA; i++) // Currently a stupid method
		{
			if (hashTable->chain[i] == nullptr)continue;
			hashTable->head = hashTable->chain[i];
			while (hashTable->head != nullptr)
			{
				if (hashTable->head->data != nullptr)
				{
					ofs << hashTable->head->data << "\n";
				}
				hashTable->head = hashTable->head->next;
			}
		}
	}
	ofs.close();
}

void hashTable::read(hashTable::HASH_TABLE* hashTable, const std::string& file)
{
	std::string data;
	std::ifstream ifs(file, std::ios_base::in);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << file << std::endl;
	}
	else
	{
		while (!ifs.eof())
		{
			ifs >> data;
			insert(hashTable, data.c_str());
		}
	}
	ifs.close();
}

bool hashTable::insert(hashTable::HASH_TABLE* hashTable, const char* data)
{
	if (hashTable == nullptr)
		return false;

	if (hashTable->chain[BKDRHash(data)]->data == nullptr)
	{
		NODE* node = create_node(hashTable->size);

		strcpy(node->data, data);
		node->next = nullptr;
		hashTable->chain[BKDRHash(data)]->data = node->data;
		hashTable->chain[BKDRHash(data)]->next = node->next;

		free(node);
		return true;
	}
	else
	{
		hashTable->head = customerId->chain[BKDRHash(data)];
		while (hashTable->head->next != nullptr)
			hashTable->head = customerId->head->next;
		hashTable->head->next = create_node(hashTable->size);

		strcpy(hashTable->head->next->data, data);
		hashTable->head->next->next = nullptr;

		return true;
	}
}

hashTable::hashTable()
{
	create_hash();
	read(flightName, "flightName.hash.data");
	read(customerId, "customerId.hash.data");
	read(customerName, "customerName.hash.data");
}

hashTable::~hashTable()
{
	save(flightName, "flightName.hash.data");
	save(customerId, "customerId.hash.data");
	save(customerName, "customerName.hash.data");
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
	return insert(flightName, data);
}

bool hashTable::insert_customer_id(char* data)
{
	return insert(customerId, data);
}

bool hashTable::insert_customer_name(char* data)
{
	return insert(customerName, data);
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
