/**
 * @file Flight.h
 * @brief Flight Service
 * @details the interface to manipulate with customer
 * @author yhl & Paul
 * @version 0.0.1
 */

#ifndef FLIGHTTICKET_SERVICE_FLIGHT_H_
#define FLIGHTTICKET_SERVICE_FLIGHT_H_

#include "service.h"
#include "../model/definitions.h"
#include "../model/LinearEngine.h"

namespace Service
{
	/**
	 * @brief flight service
	 */
	class Flight
	{
	 public:
		explicit Flight(const char* flightName);
		~Flight();
		bool AddFlight(const char* departure, const char* destination, int maxCapacity, time_t time);
		void DeleteFlight();
		static void PrintFlights(const char* departure, const char* destination);
		void PrintCustomers();

	 private:
		int FlightId = -1;
		char FlightName[FLIGHT_NAME_MAX_SIZE / sizeof(char)]{};
		char Departure[FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)]{};
		char Destination[FLIGHT_DESTINATION_MAX_SIZE / sizeof(char)]{};
		int MaxCapacity = 0;
		int Current = 0;
		time_t Time;
		void QueryInfo();
	};
}
#endif //FLIGHTTICKET_SERVICE_FLIGHT_H_
