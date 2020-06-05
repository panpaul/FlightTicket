#ifndef FLIGHTTICKET_SERVICE_CUSTOMER_H_
#define FLIGHTTICKET_SERVICE_CUSTOMER_H_

#include "service.h"
#include "../model/definitions.h"
#include "../model/linearEngine.h"

class Customer
{
 public:
	Customer(char* name, char* id);
	~Customer();
	bool InsertCustomer();
	void PrintTickets();
	void MakeOrder(char* flightName);
	void DeleteOrder(char* flightName);

 private:
	void QueryInfo();
	int CustomerId;
	char Name[CUSTOMER_NAME_MAX_SIZE / sizeof(char)]{};
	char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]{};
};

#endif //FLIGHTTICKET_SERVICE_CUSTOMER_H_
