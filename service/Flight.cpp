#include "Flight.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <ctime>

Service::Flight::Flight(const char* flightName)
{
	int len = strlen(flightName);
	if (len >= (FLIGHT_NAME_MAX_SIZE / sizeof(char)))
	{
		throw std::invalid_argument("航班名称长度不合法 ");
	}
	strcpy(this->FlightName, flightName);
}

Service::Flight::~Flight() = default;

bool Service::Flight::AddFlight(const char* departure, const char* destination, int maxCapacity, time_t time)
{
	int lenDeparture = strlen(departure);
	int lenDestination = strlen(destination);

	if (
		lenDeparture >= (FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)) ||
		lenDestination >= (FLIGHT_DESTINATION_MAX_SIZE / sizeof(char))
		)
	{
		std::cout << "出发站/终点站名称长度不合法 " << std::endl;
		return false;
	}

	if (maxCapacity <= 0)
	{
		std::cout << "最大载客量不合法 " << std::endl;
		return false;
	}

	strcpy(this->Departure, departure);
	strcpy(this->Destination, destination);
	this->MaxCapacity = maxCapacity;
	this->Time = time;

	db::Flight flight{};
	strcpy(flight.FlightName, FlightName);
	strcpy(flight.Departure, Departure);
	strcpy(flight.Destination, Destination);
	flight.MaxCapacity = MaxCapacity;
	flight.Current = 0;
	flight.Time = Time;

	int id = engine->InsertFlight(flight);
	if (id == -1)
	{
		std::cout << "航班添加失败 " << std::endl;
		return false;
	}
	FlightId = id;

	std::cout << "航班添加成功 " << std::endl;

	return true;
}

void Service::Flight::DeleteFlight()
{
	QueryInfo();

	if (FlightId == 0)
	{
		std::cout << "未查询到此航班 " << std::endl;
		return;
	}

	bool status = engine->DeleteFlight(FlightId);
	if (status)
		std::cout << "成功删除航班 " << std::endl;
	else
		std::cout << "航班删除失败 " << std::endl;

}

void Service::Flight::PrintFlights(const char* departure, const char* destination)
{
	int lenDeparture = strlen(departure);
	int lenDestination = strlen(destination);

	if (
		lenDeparture >= (FLIGHT_DEPARTURE_MAX_SIZE / sizeof(char)) ||
		lenDestination >= (FLIGHT_DESTINATION_MAX_SIZE / sizeof(char))
		)
	{
		std::cout << "出发站/终点站名称长度不合法 " << std::endl;
		return;
	}

	db::Flight flight{};
	strcpy(flight.Departure, departure);
	strcpy(flight.Destination, destination);

	auto flightVec = engine->QueryFlight(flight);
	if (flightVec.empty())
	{
		std::cout << "未查询到相关航班 " << std::endl;
		return;
	}

	std::cout << "-------------------------" << std::endl;
	for (auto& i : flightVec)
	{
		std::cout << "航班名: " << i.FlightName << std::endl;
		std::cout << "始发站: " << i.Departure << std::endl;
		std::cout << "终点站: " << i.Destination << std::endl;
		std::cout << "剩余座位: " << i.MaxCapacity - i.Current << std::endl;
		char mbStr[100];
		if (std::strftime(mbStr, sizeof(mbStr), "%a %H:%M:%S", std::gmtime(&i.Time)))
		{
			std::cout << "出发时间: " << mbStr << '\n';
		}
		std::cout << "-------------------------" << std::endl;
	}
}

void Service::Flight::PrintCustomers()
{
	QueryInfo();

	db::Order order{};
	order.FlightId = FlightId;
	auto orderVec = engine->QueryOrder(order);
	if (orderVec.empty())
	{
		std::cout << "未查询到相关乘客 " << std::endl;
		return;
	}

	std::cout << "-------------------------" << std::endl;
	for (auto& i : orderVec)
	{
		db::Customer customer{};
		customer.CustomerId = i.CustomerId;
		auto customerVec = engine->QueryCustomer(customer);

		std::cout << "姓名: " << customerVec[0].Name << std::endl;
		std::cout << "证件号: " << customerVec[0].Id << std::endl;
		std::cout << "座位号: " << i.SeatId << std::endl;
		std::cout << "-------------------------" << std::endl;
	}
}

void Service::Flight::QueryInfo()
{
	if (FlightId > 0) return;

	db::Flight flight{};
	flight.FlightId = 0;
	strcpy(flight.FlightName, FlightName);

	auto vec = engine->QueryFlight(flight);
	if (!vec.empty())
	{
		FlightId = vec[0].FlightId;
		strcpy(this->Departure, vec[0].Departure);
		strcpy(this->Destination, vec[0].Destination);
		this->MaxCapacity = vec[0].MaxCapacity;
		this->Current = vec[0].Current;
		this->Time = vec[0].Time;
	}
}
