//
// Created by panyuxuan on 2020/5/7.
//

#ifndef FLIGHTTICKET_SERVICE_CUSTOMER_H_
#define FLIGHTTICKET_SERVICE_CUSTOMER_H_

#include "../definitions.h"
#include <cwchar>
#include <cstring>
#include <stdexcept>

// debug only
#include <iostream>

class customer
{
 private:
	wchar_t Name[CUSTOMER_NAME_MAX_SIZE / sizeof(wchar_t)]{};
	char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]{};
	int FlightId{};
	int SeatId{};

 public:
	explicit customer(wchar_t* name);
	~customer();
	bool query();
	void new_customer(char* id);
	bool order(int flight_id);
};

#endif //FLIGHTTICKET_SERVICE_CUSTOMER_H_
