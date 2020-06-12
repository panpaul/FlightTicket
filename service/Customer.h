/**
 * @file Customer.h
 * @brief Customer Service
 * @details the interface to manipulate with customer
 * @author yhl & Paul
 * @version 0.0.1
 */

#ifndef FLIGHTTICKET_SERVICE_CUSTOMER_H_
#define FLIGHTTICKET_SERVICE_CUSTOMER_H_

#include "service.h"
#include "../model/definitions.h"
#include "../model/LinearEngine.h"

namespace Service
{
	/**
	 * @brief customer service
	 */
	class Customer
	{
	 public:
		Customer(const char* name, const char* id);
		~Customer();
		bool AddCustomer();
		void PrintTickets();
		void MakeOrder(const char* flightName);
		void DeleteOrder(const char* flightName);

	 private:
		void QueryInfo();
		int CustomerId = -1;
		char Name[CUSTOMER_NAME_MAX_SIZE / sizeof(char)]{};
		char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]{};
	};
}
#endif //FLIGHTTICKET_SERVICE_CUSTOMER_H_
