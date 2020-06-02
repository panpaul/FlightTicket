//
// Created by panyuxuan on 2020/5/7.
//

#include "flight.h"
#include <cstring>

flight::flight()
{

}

bool flight::query(const char* dest)
{
	db::Flight flightStruct{};
	strcpy(flightStruct.Destination, dest);
	auto flight = engine->QueryFlight(flightStruct);
	if (flight.FlightId == 0)return false;

	this->FlightId = flight.FlightId;
	strcpy(this->FlightName, flight.FlightName);
	strcpy(this->Departure, flight.Departure);
	strcpy(this->Destination, flight.Destination);
	this->MaxCapacity = flight.MaxCapacity;
	this->Current = flight.Current;
	return true;
}

bool flight::new_flight()
{
	return false;
}

bool flight::delete_flight()
{
	return false;
}

flight::~flight()
= default;
