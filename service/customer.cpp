//
// Created by panyuxuan on 2020/5/7.
//

#include "customer.h"

customer::customer(char* name)
{
	auto len = strlen(name);
	if (len * sizeof(char) >= CUSTOMER_NAME_MAX_SIZE)
	{
		throw std::invalid_argument("name too long");
	}
	strcpy(this->Name, name);

	memset(this->Id, 0, CUSTOMER_ID_MAX_SIZE);
	this->FlightId = 0;
	this->SeatId = 0;
}

customer::~customer()
= default;

bool customer::query()
{
	std::cout << Name << std::endl;
	return true;
}

void customer::new_customer(char* id)
{
	auto len = strlen(id);
	if (len * sizeof(char) >= CUSTOMER_ID_MAX_SIZE)
	{
		throw std::invalid_argument("id too long");
	}
	strcpy(this->Id, id);
}

bool customer::order(int flight_id)
{
	return this->SeatId;
}

