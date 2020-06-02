//
// Created by panyuxuan on 2020/5/7.
//

#ifndef FLIGHTTICKET_SERVICE_FLIGHT_H_
#define FLIGHTTICKET_SERVICE_FLIGHT_H_

#include "../definitions.h"
#include "service.h"

class flight
{ // TODO make a wrapper function
 public:
	int FlightId{};
	char FlightName[FLIGHT_NAME_MAX_SIZE / sizeof(char)]{};
	char Departure[FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)]{};
	char Destination[FLIGHT_DESTINATION_MAX_SIZE / sizeof(char)]{};
	int MaxCapacity{};
	int Current{};

	flight();
	~flight();
	bool query(const char* dest);
	bool new_flight();
	bool delete_flight();

};

#endif //FLIGHTTICKET_SERVICE_FLIGHT_H_
