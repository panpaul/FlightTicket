/**
 * @file struct.h
 * @brief definitions of the structures used in model
 * @details includes the structures of flight, customer, order
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#ifndef _MODEL_H_
#define _MODEL_H_

namespace db
{
#include "definitions.h"

	struct Flight /// @brief the structure of flight info
	{
		int FlightId; ///< unique index marking the id
		char FlightName[FLIGHT_NAME_MAX_SIZE / sizeof(char)]; ///< the name of the flight(unique)
		char Departure[FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)]; ///< the name of the departure
		char Destination[FLIGHT_DESTINATION_MAX_SIZE / sizeof(char)]; ///< the name of the destination
		int MaxCapacity; ///< max passengers num
		int Current; ///< current ordered passengers num
		time_t Time; ///< when to fly
	};
	const int FLIGHT_SIZE = sizeof(Flight);

	struct Customer /// @brief the structure of customer info
	{
		int CustomerId; ///< unique index marking the id
		char Name[CUSTOMER_NAME_MAX_SIZE / sizeof(char)]; ///< customer's name
		char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]; ///< passport id / ID card number(unique)
	};
	const int CUSTOMER_SIZE = sizeof(Customer);

	struct Order /// @brief the structure of order info
	{
		int OrderId; ///< unique index marking the id
		int CustomerId; ///< customer's index
		int FlightId; ///< flight's index
		int SeatId; ///< seat id
	};
	const int ORDER_SIZE = sizeof(Order);
}
#endif //_MODEL_H_
