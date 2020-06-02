//
// Created by panyuxuan on 2020/5/7.
//

#ifndef FLIGHTTICKET_SERVICE_CUSTOMER_H_
#define FLIGHTTICKET_SERVICE_CUSTOMER_H_

#include "service.h"
#include "../definitions.h"
#include <cstring>
#include <stdexcept>

// debug only
#include <iostream>

class customer
{ // TODO make a wrapper function
 public:
	int CustomerId{};
	char Name[CUSTOMER_NAME_MAX_SIZE / sizeof(char)]{};
	char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]{};
	int FlightId{};
	int SeatId{};

	customer();
	customer(char* name, char* id);
	~customer();
	bool query();
	void new_customer(const char* name, const char* id);
	bool order(int flight_id);
};

#endif //FLIGHTTICKET_SERVICE_CUSTOMER_H_
