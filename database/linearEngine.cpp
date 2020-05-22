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
	saveVec(flightVec, FLIGHT_SIZE, basePath + "/flight.data");
	saveVec(customerVec, CUSTOMER_SIZE, basePath + "/customer.data");
	saveVec(orderVec, ORDER_SIZE, basePath + "/order.data");
}

template<typename T>
void db::linearEngine::saveVec(std::vector<T>& vec, int size, const std::string& file)
{
	std::ofstream ofs(file,
		std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	if (!ofs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << file << std::endl;
		return;
	}

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
