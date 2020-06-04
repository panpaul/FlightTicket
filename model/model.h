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

#include "../definitions.h"

namespace db
{
	struct Flight /// @brief the structure of flight info
	{
		int FlightId;
		char FlightName[FLIGHT_NAME_MAX_SIZE / sizeof(char)];
		char Departure[FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)];
		char Destination[FLIGHT_DESTINATION_MAX_SIZE / sizeof(char)];
		int MaxCapacity; ///< max passengers num
		int Current; ///< current ordered passengers num
	};
	const int FLIGHT_SIZE = sizeof(Flight);

	struct Customer /// @brief the structure of customer info
	{
		int CustomerId;
		char Name[CUSTOMER_NAME_MAX_SIZE / sizeof(char)];
		char Id[CUSTOMER_ID_MAX_SIZE / sizeof(char)]; ///< passport id / ID card number
	};
	const int CUSTOMER_SIZE = sizeof(Customer);

	struct Order /// @brief the structure of order info
	{
		int OrderId;
		int CustomerId;
		int FlightId;
		int SeatId;
	};
	const int ORDER_SIZE = sizeof(Order);
}
#endif //_MODEL_H_
