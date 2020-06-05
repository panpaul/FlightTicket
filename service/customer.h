//
// Created by panyuxuan on 2020/5/7.
//

#ifndef FLIGHTTICKET_SERVICE_CUSTOMER_H_
#define FLIGHTTICKET_SERVICE_CUSTOMER_H_

#include "service.h"
#include "../model/definitions.h"
#include "../model/linearEngine.h"
#include <cstring>

// debug only
#include <iostream>

class customer
{ // TODO make a wrapper function
 public:
	customer();
	customer(char* name, char* id);
	~customer();
	void InsertCustomer();
	void QueryCustomer();
	void MakeOrder(char* flightname);
	void DeleteOrder();
 private:
	bool flag = false;
	int CustomerID;
	char name[CUSTOMER_NAME_MAX_SIZE/sizeof(char)];
	char id[CUSTOMER_ID_MAX_SIZE/sizeof(char)];
};

#endif //FLIGHTTICKET_SERVICE_CUSTOMER_H_
