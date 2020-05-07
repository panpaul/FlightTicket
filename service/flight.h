//
// Created by panyuxuan on 2020/5/7.
//

#ifndef FLIGHTTICKET_SERVICE_FLIGHT_H_
#define FLIGHTTICKET_SERVICE_FLIGHT_H_

#include "../definitions.h"

class flight
{
 private:
	int FlightId{};
	wchar_t FlightName[FLIGHT_NAME_MAX_SIZE / sizeof(wchar_t)]{};
	wchar_t Departure{};
	wchar_t Destination{};
	int MaxCapacity{};
	int Current{};

 public:
	flight();
	~flight();
	static flight* query();
	static bool new_flight();
	static bool delete_flight();
};

#endif //FLIGHTTICKET_SERVICE_FLIGHT_H_