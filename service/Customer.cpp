#include "Customer.h"
#include <cstring>
#include <iostream>
#include <ctime>

Service::Customer::Customer(const char* name, const char* id)
{
	auto lenName = strlen(name);
	auto lenId = strlen(id);
	if (
		lenName >= (CUSTOMER_NAME_MAX_SIZE / sizeof(char)) ||
		lenId >= (CUSTOMER_ID_MAX_SIZE / sizeof(char))
		)
	{
		throw std::invalid_argument("姓名或身份信息长度不合法");
	}
	strcpy(this->Name, name);
	strcpy(this->Id, id);
	QueryInfo();
}

Service::Customer::~Customer()
= default;

/**
 * @brief Add customer into model
 * @return true for success and false for error
 */
bool Service::Customer::AddCustomer()
{
	db::Customer customer{};
	strcpy(customer.Name, this->Name);
	strcpy(customer.Id, this->Id);
	int id = engine->InsertCustomer(customer);
	if (id == -1)return false;
	CustomerId = id;
	return true;
}

/**
 * @brief fetch customer's info
 */
void Service::Customer::QueryInfo()
{
	if (CustomerId > 0)
		return;
	db::Customer customer{};
	customer.CustomerId = 0;
	strcpy(customer.Name, Name);
	strcpy(customer.Id, Id);
	auto vec = engine->QueryCustomer(customer);
	if (!vec.empty())
	{
		CustomerId = vec[0].CustomerId;
	}
}

/**
 * @brief print all tickets into stdout
 */
void Service::Customer::PrintTickets()
{
	db::Order order{ 0, CustomerId, 0, 0 };
	auto orderVec = engine->QueryOrder(order);

	if (orderVec.empty())
	{
		std::cout << "未查询到相关信息" << std::endl;
		return;
	}
	for (auto i:orderVec)
	{
		db::Flight flight{ i.FlightId };
		auto flightVec = engine->QueryFlight(flight);
		std::cout << "-------------------------" << std::endl;
		std::cout << "航班号: " << flightVec[0].FlightName << std::endl;
		std::cout << "始发地: " << flightVec[0].Departure << std::endl;
		std::cout << "目的地: " << flightVec[0].Destination << std::endl;
		char mbStr[100];
		if (std::strftime(mbStr, sizeof(mbStr), "%a %H:%M:%S", std::gmtime(&flightVec[0].Time)))
		{
			std::cout << "出发时间: " << mbStr << '\n';
		}
		std::cout << "座位号: " << i.SeatId << std::endl;
	}
	std::cout << "-------------------------" << std::endl;
}

/**
 * @brief make an order
 * @param flightName the name of the flight to be ordered
 */
void Service::Customer::MakeOrder(const char* flightName)
{
	if (CustomerId <= 0)
	{
		bool status = AddCustomer();
		if (!status)
		{
			std::cout << "无法创建乘客信息" << std::endl;
			return;
		}
	}

	if (strlen(flightName) >= (FLIGHT_NAME_MAX_SIZE / sizeof(char)))
	{
		//throw std::invalid_argument("航班名称不合法");
		std::cout << "航班名称不合法 " << std::endl;
		return;
	}

	db::Flight flight{};
	strcpy(flight.FlightName, flightName);
	auto flightVec = engine->QueryFlight(flight);
	if (flightVec.empty())
	{
		//throw std::invalid_argument("航班名称不存在，请检查输入");
		std::cout << "航班名称不存在，请检查输入 " << std::endl;
		return;
	}

	if (flightVec[0].MaxCapacity - flightVec[0].Current <= 0)
	{
		std::cout << "本航班已满员 " << std::endl;
		return;
	}

	db::Order order{ 0, CustomerId, flightVec[0].FlightId, flightVec[0].Current + 1 };

	auto judge = engine->InsertOrder(order);
	if (judge == -1)
	{
		std::cout << "抱歉，航空公司规定对于每次航班一人仅能购买一张票，请重试 " << std::endl;
		return;
	}

	flightVec[0].Current++;
	engine->UpdateFlight(flightVec[0]);

	std::cout << "订票成功 " << std::endl;

}

/**
 * @brief delete an order
 * @param flightName the name of the flight to be deleted
 */
void Service::Customer::DeleteOrder(const char* flightName)
{
	if (strlen(flightName) >= (FLIGHT_NAME_MAX_SIZE / sizeof(char)))
	{
		std::cout << "航班名称不合法 " << std::endl;
		return;
	}

	db::Flight flight{};
	strcpy(flight.FlightName, flightName);
	auto flightVec = engine->QueryFlight(flight);
	if (flightVec.empty())
	{
		std::cout << "航班名称不存在，请检查输入 " << std::endl;
		return;
	}

	db::Order order{ 0, CustomerId, flightVec[0].FlightId };
	auto orderVec = engine->QueryOrder(order);

	if (orderVec.empty())
	{
		std::cout << "抱歉，您并没有购买本次航班的票，请检查输入的身份信息及航班 " << std::endl;
		return;
	}

	bool status = engine->DeleteOrder(orderVec[0].OrderId);
	if (status)std::cout << "订单删除成功 " << std::endl;
	else
		std::cout << "订单删除失败 " << std::endl;

	flightVec[0].Current--;
	engine->UpdateFlight(flightVec[0]);
}
