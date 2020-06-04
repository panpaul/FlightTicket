/**
 * @file linearEngine.cpp
 * @brief the basic storage engine used in model
 * @details file I/O, basic query with O(n). Notice: All field is unique
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.2
 * @date 2020-5-22
 */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ranges>
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
 * @version 0.0.2
 */
bool db::linearEngine::InsertFlight(struct Flight flight)
{
	flight.FlightId = 0;

	auto f = QueryFlight(flight);
	if (f.size() != 0) // existed
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
 * @version 0.0.2
 */
bool db::linearEngine::InsertCustomer(db::Customer customer)
{
	customer.CustomerId = 0;

	auto c = QueryCustomer(customer);
	if (c.size() != 0) // existed
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
 * @version 0.0.2
 */
bool db::linearEngine::InsertOrder(db::Order order)
{
	order.OrderId = 0;

	auto o = QueryOrder(order);
	if (o.size() != 0) // existed
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
std::vector<db::Flight> db::linearEngine::QueryFlight(struct Flight flight)
{
	if (flight.FlightId != 0)
	{
		auto filter = [flight](db::Flight f)
		{
		  return f.FlightId == flight.FlightId;
		};
		return findMatch(flightVec, filter);
	}
	else if (flight.FlightName[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.FlightName, flight.FlightName) == 0;
		};
		return findMatch(flightVec, filter);
	}
	else if (flight.Departure[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.Departure, flight.Departure) == 0;
		};
		return findMatch(flightVec, filter);
	}
	else if (flight.Destination[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.Destination, flight.Destination) == 0;
		};
		return findMatch(flightVec, filter);
	}
	else
	{
		std::vector<db::Flight> empty;
		return empty;
	}
}

/**
 * @brief query a customer info
 * @details it will match the first none "NULL" field
 * @param customer the query parameter
 * @return the desired data for success or "NULL" for error
 */
std::vector<db::Customer> db::linearEngine::QueryCustomer(db::Customer customer)
{
	if (customer.CustomerId != 0)
	{
		auto filter = [customer](db::Customer c)
		{
		  return c.CustomerId == customer.CustomerId;
		};
		return findMatch(customerVec, filter);
	}
	else if (customer.Name[0] != '\0')
	{
		auto filter = [customer](db::Customer c)
		{
		  return strcmp(c.Name, customer.Name) == 0;
		};
		return findMatch(customerVec, filter);
	}
	else if (customer.Id[0] != '\0')
	{
		auto filter = [customer](db::Customer c)
		{
		  return strcmp(c.Id, customer.Id) == 0;
		};
		return findMatch(customerVec, filter);
	}
	else
	{
		std::vector<db::Customer> empty;
		return empty;
	}
}

/**
 * @brief query an order info
 * @details it will match the first none "NULL" field
 * @param order the query parameter
 * @return the desired data for success or "NULL" for error
 */
std::vector<db::Order> db::linearEngine::QueryOrder(db::Order order)
{
	if (order.OrderId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.OrderId == order.OrderId;
		};
		return findMatch(orderVec, filter);
	}
	else if (order.CustomerId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.CustomerId == order.CustomerId;
		};
		return findMatch(orderVec, filter);
	}
	else if (order.FlightId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.FlightId == order.FlightId;
		};
		return findMatch(orderVec, filter);
	}
	else
	{
		std::vector<db::Order> empty;
		return empty;
	}
}

/**
 * @brief delete a flight info from memory
 * @param flightId the flight info to be deleted
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::DeleteFlight(int flightId)
{
	for (auto iter = flightVec.begin(); iter != flightVec.end(); ++iter)
	{
		if (iter->FlightId == flightId)
		{
			flightVec.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * @brief delete a customer info from memory
 * @param customerId the flight info to be deleted
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::DeleteCustomer(int customerId)
{
	for (auto iter = customerVec.begin(); iter != customerVec.end(); ++iter)
	{
		if (iter->CustomerId == customerId)
		{
			customerVec.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * @brief delete an order info from memory
 * @param orderId the flight info to be deleted
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::DeleteOrder(int orderId)
{
	for (auto iter = orderVec.begin(); iter != orderVec.end(); ++iter)
	{
		if (iter->OrderId == orderId)
		{
			orderVec.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * @brief update flight info
 * @details FlightId must not be zero
 * @param flight update info
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::UpdateFlight(db::Flight flight)
{
	if (flight.FlightId == 0)return false;
	for (auto& i : flightVec)
	{
		if (i.FlightId == flight.FlightId)
		{
			memcpy(i.FlightName, flight.FlightName, FLIGHT_NAME_MAX_SIZE);
			memcpy(i.Departure, flight.Departure, FLIGHT_DEPARTURE_MAX_SIZE);
			memcpy(i.Destination, flight.Destination, FLIGHT_DESTINATION_MAX_SIZE);
			i.MaxCapacity = flight.MaxCapacity;
			i.Current = flight.Current;
			return true;
		}
	}
	return false;
}

/**
 * @brief update customer info
 * @details CustomerId must not be zero
 * @param customer update info
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::UpdateCustomer(db::Customer customer)
{
	if (customer.CustomerId == 0)return false;
	for (auto& i : customerVec)
	{
		if (i.CustomerId == customer.CustomerId)
		{
			memcpy(i.Name, customer.Name, CUSTOMER_NAME_MAX_SIZE);
			memcpy(i.Id, customer.Id, CUSTOMER_ID_MAX_SIZE);
			return true;
		}
	}
	return false;
}

/**
 * @brief update order info
 * @details OrderId must not be zero
 * @param order update info
 * @return true for success and false for error
 * @version 0.0.1
 */
bool db::linearEngine::UpdateOrder(db::Order order)
{
	if (order.OrderId == 0)return false;
	for (auto& i : orderVec)
	{
		if (i.OrderId == order.OrderId)
		{
			i.CustomerId = order.CustomerId;
			i.FlightId = order.FlightId;
			i.SeatId = order.SeatId;
			return true;
		}
	}
	return false;
}

template<typename T, typename Cmp>
std::vector<T> db::linearEngine::findMatch(std::vector<T>& vec, Cmp filter)
{
	std::vector<T> ret;
	auto result = vec | std::views::filter(filter);
	for (auto i : result)
	{
		ret.push_back(i);
	}
	return ret;
}
