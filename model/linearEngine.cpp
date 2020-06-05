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
#include "linearEngine.h"

#ifdef USING_FALLBACK_SUPPORT
#include <range/v3/all.hpp>

#else
#include <ranges>

#endif

db::linearEngine::linearEngine(const std::string& path)
{
	BasePath = path;
	LoadFlightVec();
	LoadCustomerVec();
	LoadOrderVec();
}

db::linearEngine::~linearEngine()
{
	SaveVec(FlightVec, FlightIdCnt, FLIGHT_SIZE, BasePath + "/flight.data");
	SaveVec(CustomerVec, CustomerIdCnt, CUSTOMER_SIZE, BasePath + "/customer.data");
	SaveVec(OrderVec, OrderIdCnt, ORDER_SIZE, BasePath + "/order.data");
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
void db::linearEngine::SaveVec(std::vector<T>& vec, int cnt, int size, const std::string& file)
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

void db::linearEngine::LoadFlightVec()
{
	char data[FLIGHT_SIZE + 1];
	struct Flight flight{};
	std::ifstream ifs(BasePath + "/flight.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << BasePath + "/flight.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&FlightIdCnt), sizeof(int));

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
		cnt += sizeof(int);
		memcpy(&flight.Time, data + cnt, sizeof(time_t));
		FlightVec.push_back(flight);
	}

	ifs.close();
}

void db::linearEngine::LoadCustomerVec()
{
	char data[CUSTOMER_SIZE + 1];
	struct Customer customer{};
	std::ifstream ifs(BasePath + "/customer.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << BasePath + "/customer.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&CustomerIdCnt), sizeof(int));

	while (ifs.read(data, FLIGHT_SIZE))
	{
		int cnt = 0;
		memcpy(&customer.CustomerId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&customer.Name, data + cnt, CUSTOMER_NAME_MAX_SIZE);
		cnt += CUSTOMER_NAME_MAX_SIZE;
		memcpy(&customer.Id, data + cnt, CUSTOMER_ID_MAX_SIZE);

		CustomerVec.push_back(customer);
	}

	ifs.close();
}

void db::linearEngine::LoadOrderVec()
{
	char data[ORDER_SIZE + 1];
	struct Order order{};
	std::ifstream ifs(BasePath + "/order.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << BasePath + "/order.data" << std::endl;
		return;
	}

	ifs.read(reinterpret_cast<char*>(&OrderIdCnt), sizeof(int));

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
		OrderVec.push_back(order);
	}

	ifs.close();
}

/**
 * @brief insert a flight info into memory
 * @details the field flightId will be auto computed and no duplicate data will be inserted
 * @param flight the struct of flight to be inserted
 * @return FlightId for success and -1 for error
 * @version 0.0.3
 */
int db::linearEngine::InsertFlight(struct Flight flight)
{
	flight.FlightId = 0;

	auto f = QueryFlight(flight);
	if (!f.empty()) // existed
	{
		std::cerr << "Flight Existed" << std::endl;
		return -1;
	}

	flight.FlightId = ++FlightIdCnt;
	FlightVec.push_back(flight);

	return flight.FlightId;
}

/**
 * @brief insert a customer info into memory
 * @details the field customerId will be auto computed and no duplicate data will be inserted
 * @param customer the struct of customer to be inserted
 * @return CustomerId for success and -1 for error
 * @version 0.0.3
 */
int db::linearEngine::InsertCustomer(db::Customer customer)
{
	customer.CustomerId = 0;
	char backup = customer.Name[0];
	customer.Name[0] = '\0';

	auto c = QueryCustomer(customer);
	if (!c.empty()) // existed
	{
		std::cerr << "Customer Existed" << std::endl;
		return -1;
	}

	customer.Name[0] = backup;
	customer.CustomerId = ++CustomerIdCnt;
	CustomerVec.push_back(customer);

	return customer.CustomerId;
}

/**
 * @brief insert a order info into memory
 * @details (it will not check whether customerId or flightId existed or not)
 * the field orderId will be auto computed and no duplicate data will be inserted
 * @param order the struct of order to be inserted
 * @return OrderId for success and -1 for error
 * @version 0.0.3
 */
int db::linearEngine::InsertOrder(db::Order order)
{
	order.OrderId = 0;

	auto o = QueryOrder(order);
	if (!o.empty()) // existed
	{
		std::cerr << "Order Existed" << std::endl;
		return -1;
	}

	order.OrderId = ++OrderIdCnt;
	OrderVec.push_back(order);

	return order.OrderId;
}

/**
 * @brief query a flight info
 * @details it will match the first none "NULL" field
 * @param flight the query parameter
 * @return the desired data
 */
std::vector<db::Flight> db::linearEngine::QueryFlight(struct Flight flight)
{
	if (flight.FlightId != 0)
	{
		auto filter = [flight](db::Flight f)
		{
		  return f.FlightId == flight.FlightId;
		};
		return FindMatch(FlightVec, filter);
	}
	else if (flight.FlightName[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.FlightName, flight.FlightName) == 0;
		};
		return FindMatch(FlightVec, filter);
	}
	else if (flight.Departure[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.Departure, flight.Departure) == 0;
		};
		return FindMatch(FlightVec, filter);
	}
	else if (flight.Destination[0] != '\0')
	{
		auto filter = [flight](db::Flight f)
		{
		  return strcmp(f.Destination, flight.Destination) == 0;
		};
		return FindMatch(FlightVec, filter);
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
 * @return the desired data
 */
std::vector<db::Customer> db::linearEngine::QueryCustomer(db::Customer customer)
{
	if (customer.CustomerId != 0)
	{
		auto filter = [customer](db::Customer c)
		{
		  return c.CustomerId == customer.CustomerId;
		};
		return FindMatch(CustomerVec, filter);
	}
	else if (customer.Name[0] != '\0')
	{
		auto filter = [customer](db::Customer c)
		{
		  return strcmp(c.Name, customer.Name) == 0;
		};
		return FindMatch(CustomerVec, filter);
	}
	else if (customer.Id[0] != '\0')
	{
		auto filter = [customer](db::Customer c)
		{
		  return strcmp(c.Id, customer.Id) == 0;
		};
		return FindMatch(CustomerVec, filter);
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
 * @return the desired data
 */
std::vector<db::Order> db::linearEngine::QueryOrder(db::Order order)
{
	if (order.OrderId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.OrderId == order.OrderId;
		};
		return FindMatch(OrderVec, filter);
	}
	else if (order.CustomerId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.CustomerId == order.CustomerId;
		};
		return FindMatch(OrderVec, filter);
	}
	else if (order.FlightId != 0)
	{
		auto filter = [order](db::Order o)
		{
		  return o.FlightId == order.FlightId;
		};
		return FindMatch(OrderVec, filter);
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
	for (auto iter = FlightVec.begin(); iter != FlightVec.end(); ++iter)
	{
		if (iter->FlightId == flightId)
		{
			FlightVec.erase(iter);
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
	for (auto iter = CustomerVec.begin(); iter != CustomerVec.end(); ++iter)
	{
		if (iter->CustomerId == customerId)
		{
			CustomerVec.erase(iter);
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
	for (auto iter = OrderVec.begin(); iter != OrderVec.end(); ++iter)
	{
		if (iter->OrderId == orderId)
		{
			OrderVec.erase(iter);
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
	for (auto& i : FlightVec)
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
	for (auto& i : CustomerVec)
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
	for (auto& i : OrderVec)
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

/**
 * @brief find all data matching the filter
 * @tparam T type of the data
 * @tparam Cmp the lambda function
 * @param vec domain of the data
 * @param filter condition to match
 * @return a vector storing the data
 * @version 0.0.1
 */
template<typename T, typename Cmp>
std::vector<T> db::linearEngine::FindMatch(std::vector<T>& vec, Cmp filter)
{
	std::vector<T> ret;

#ifdef USING_FALLBACK_SUPPORT
	auto result = vec | ranges::views::filter(filter);
#else
	auto result = vec | std::views::filter(filter);
#endif

	for (auto i : result)
	{
		ret.push_back(i);
	}
	return ret;
}
