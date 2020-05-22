/**
 * @file linearEngine.cpp
 * @brief the basic storage engine used in database
 * @details file I/O, basic query with O(n)
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "linearEngine.h"

db::linearEngine::linearEngine(const std::string& path)
{
	basePath = path;
	loadFlightVec();
	loadCustomerVec();
	loadOrderVec();
}

db::linearEngine::~linearEngine()
{
	saveVec(flightVec, flightIdCnt, FLIGHT_SIZE, basePath + "/flight.data");
	saveVec(customerVec, customerIdCnt, CUSTOMER_SIZE, basePath + "/customer.data");
	saveVec(orderVec, orderIdCnt, ORDER_SIZE, basePath + "/order.data");
}

/**
 * @brief save flight/customer/order vector info into dot data files
 * @tparam T type of the vector
 * @param vec the vector to be saved
 * @param cnt auto increment id number
 * @param size size of a single line of datium
 * @param file the file path of the data
 */
template<typename T>
void db::linearEngine::saveVec(std::vector<T>& vec, int cnt, int size, const std::string& file)
{
	std::ofstream ofs(file,
		std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	if (!ofs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << file << std::endl;
		return;
	}

	ofs.write(reinterpret_cast<const char*>(&cnt), sizeof(int));

	for (auto& i : vec)
	{
		ofs.write(reinterpret_cast<const char*>(&i), size);
		//ofs << "\n";
	}

	ofs.close();
}

void db::linearEngine::loadFlightVec()
{
	char data[FLIGHT_SIZE + 1];
	struct Flight flight{};
	std::ifstream ifs(basePath + "/flight.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << basePath + "/flight.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&flightIdCnt), sizeof(int));

	while (ifs.read(data, FLIGHT_SIZE))
	{
		int cnt = 0;
		memcpy(&flight.FlightId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&flight.FlightName, data + cnt, FLIGHT_NAME_MAX_SIZE);
		cnt += FLIGHT_NAME_MAX_SIZE;
		memcpy(&flight.Departure, data + cnt, FLIGHT_DEPARTURE_MAX_SIZE);
		cnt += FLIGHT_DEPARTURE_MAX_SIZE;
		memcpy(&flight.Destination, data + cnt, FLIGHT_DESTINATION_MAX_SIZE);
		cnt += FLIGHT_DESTINATION_MAX_SIZE;
		memcpy(&flight.MaxCapacity, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&flight.Current, data + cnt, sizeof(int));

		flightVec.push_back(flight);
	}

	ifs.close();
}

void db::linearEngine::loadCustomerVec()
{
	char data[CUSTOMER_SIZE + 1];
	struct Customer customer{};
	std::ifstream ifs(basePath + "/customer.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << basePath + "/customer.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&customerIdCnt), sizeof(int));

	while (ifs.read(data, FLIGHT_SIZE))
	{
		int cnt = 0;
		memcpy(&customer.CustomerId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&customer.Name, data + cnt, CUSTOMER_NAME_MAX_SIZE);
		cnt += CUSTOMER_NAME_MAX_SIZE;
		memcpy(&customer.Id, data + cnt, CUSTOMER_ID_MAX_SIZE);

		customerVec.push_back(customer);
	}

	ifs.close();
}

void db::linearEngine::loadOrderVec()
{
	char data[ORDER_SIZE + 1];
	struct Order order{};
	std::ifstream ifs(basePath + "/order.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << basePath + "/order.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&orderIdCnt), sizeof(int));

	while (ifs.read(data, FLIGHT_SIZE))
	{
		int cnt = 0;
		memcpy(&order.OrderId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&order.CustomerId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&order.FlightId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&order.SeatId, data + cnt, sizeof(int));

		orderVec.push_back(order);
	}

	ifs.close();
}

/**
 * @brief insert a flight info into memory
 * @details the field flightId will be auto computed and no duplicate data will be inserted
 * @param flight the struct of flight to be inserted
 * @return true for success and false for error
 */
bool db::linearEngine::insertFlight(struct Flight flight)
{
	flight.FlightId = 0;
	auto f = queryFlight(flight);
	if (f.FlightId != 0) // existed
	{
		std::cerr << "Flight Existed" << std::endl;
		return false;
	}
	flight.FlightId = ++flightIdCnt;
	flightVec.push_back(flight);

	return true;
}

/**
 * @brief insert a customer info into memory
 * @details the field customerId will be auto computed and no duplicate data will be inserted
 * @param customer the struct of customer to be inserted
 * @return true for success and false for error
 */
bool db::linearEngine::insertCustomer(db::Customer customer)
{
	customer.CustomerId = 0;
	auto c = queryCustomer(customer);
	if (c.CustomerId != 0) // existed
	{
		std::cerr << "Customer Existed" << std::endl;
		return false;
	}
	customer.CustomerId = ++customerIdCnt;
	customerVec.push_back(customer);

	return true;
}

/**
 * @brief insert a order info into memory
 * @details (it will not check whether customerId or flightId existed or not)
 * the field orderId will be auto computed and no duplicate data will be inserted
 * @param order the struct of order to be inserted
 * @return true for success and false for error
 */
bool db::linearEngine::insertOrder(db::Order order)
{
	order.OrderId = 0;
	auto o = queryOrder(order);
	if (o.OrderId != 0) // existed
	{
		std::cerr << "Order Existed" << std::endl;
		return false;
	}
	order.OrderId = ++orderIdCnt;
	orderVec.push_back(order);

	return true;
}

/**
 * @brief query a flight info
 * @details it will match the first none "NULL" field
 * @param flight the query parameter
 * @return the desired data for success or "NULL" for error
 */
db::Flight db::linearEngine::queryFlight(struct Flight flight)
{
	auto iter = flightVec.end();
	if (flight.FlightId != 0)
	{
		iter = std::find_if(flightVec.begin(), flightVec.end(),
			[flight](struct Flight flightCmp)
			{ return flight.FlightId == flightCmp.FlightId; }
		);
	}
	else if (flight.FlightName[0] != '\0')
	{
		iter = std::find_if(flightVec.begin(), flightVec.end(),
			[flight](struct Flight flightCmp)
			{ return !strcmp(flight.FlightName, flightCmp.FlightName); }
		);
	}
	else if (flight.Departure[0] != '\0')
	{
		iter = std::find_if(flightVec.begin(), flightVec.end(),
			[flight](struct Flight flightCmp)
			{ return !strcmp(flight.Departure, flightCmp.Departure); }
		);
	}
	else if (flight.Destination[0] != '\0')
	{
		iter = std::find_if(flightVec.begin(), flightVec.end(),
			[flight](struct Flight flightCmp)
			{ return !strcmp(flight.Destination, flightCmp.Destination); }
		);
	}

	if (iter != flightVec.end())
	{
		return *iter;
	}
	else
	{ return Flight{ 0, "", "", "", 0, 0 }; }
}

/**
 * @brief query a customer info
 * @details it will match the first none "NULL" field
 * @param customer the query parameter
 * @return the desired data for success or "NULL" for error
 */
db::Customer db::linearEngine::queryCustomer(db::Customer customer)
{
	auto iter = customerVec.end();
	if (customer.CustomerId != 0)
	{
		iter = std::find_if(customerVec.begin(), customerVec.end(),
			[customer](struct Customer customerCmp)
			{ return customer.CustomerId == customerCmp.CustomerId; }
		);
	}
	else if (customer.Name[0] != '\0')
	{
		iter = std::find_if(customerVec.begin(), customerVec.end(),
			[customer](struct Customer customerCmp)
			{ return !strcmp(customer.Name, customerCmp.Name); }
		);
	}
	else if (customer.Id[0] != '\0')
	{
		iter = std::find_if(customerVec.begin(), customerVec.end(),
			[customer](struct Customer customerCmp)
			{ return !strcmp(customer.Id, customerCmp.Id); }
		);
	}

	if (iter != customerVec.end())
	{
		return *iter;
	}
	else
	{ return Customer{ 0, "", "" }; }
}

/**
 * @brief query an order info
 * @details it will match the first none "NULL" field
 * @param order the query parameter
 * @return the desired data for success or "NULL" for error
 */
db::Order db::linearEngine::queryOrder(db::Order order)
{
	auto iter = orderVec.end();
	if (order.OrderId != 0)
	{
		iter = std::find_if(orderVec.begin(), orderVec.end(),
			[order](struct Order orderCmp)
			{ return order.OrderId == orderCmp.OrderId; }
		);
	}
	else if (order.CustomerId != 0)
	{
		iter = std::find_if(orderVec.begin(), orderVec.end(),
			[order](struct Order orderCmp)
			{ return order.CustomerId == orderCmp.CustomerId; }
		);
	}
	else if (order.FlightId != 0)
	{
		iter = std::find_if(orderVec.begin(), orderVec.end(),
			[order](struct Order orderCmp)
			{ return order.FlightId == orderCmp.FlightId; }
		);
	}

	if (iter != orderVec.end())
	{
		return *iter;
	}
	else
	{ return Order{ 0, 0, 0, 0 }; }
}
