#include "../service/Customer.h"
#include "../service/Flight.h"
#include <iostream>

using namespace std;

void Print()
{
	cout << endl;
	cout << "请选择功能: " << endl;
	cout << "\t0)退出 " << endl;
	cout << "\t1)查询航班 " << endl;
	cout << "\t2)浏览乘客订单信息 " << endl;
	cout << "\t3)浏览航班订单信息 " << endl;
	cout << "\t4)乘客订票 " << endl;
	cout << "\t5)乘客退票 " << endl;
	cout << "\t6)增加航班 " << endl;
	cout << "\t7)删除航班 " << endl;
	cout << "请输入您的选择: ";
}

void QueryFlight();
void QueryTickets();
void QueryCustomers();
void Order();
void RemoveOrder();
void InsertFlight();
void DeleteFlight();

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "");

	//Service::Setup();

	while (true)
	{
		unsigned choices;
		Print();
		cin >> choices;
		cout << endl;
		if (choices == 0)
		{
			Service::Shutdown();
			break;
		}
		if (choices > 7)
		{
			cout << "输入错误" << endl;
			continue;
		}
		switch (choices)
		{
		case 1:
			QueryFlight();
			break;
		case 2:
			QueryTickets();
			break;
		case 3:
			QueryCustomers();
			break;
		case 4:
			Order();
			break;
		case 5:
			RemoveOrder();
			break;
		case 6:
			InsertFlight();
			break;
		case 7:
			DeleteFlight();
			break;
		default:
			break;
		}
	}
	return 0;
}

void QueryFlight()
{
	string dest, dep;
	cout << "请输入起点站(任意请输入*): ";
	cin >> dep;
	cout << "请输入终点站(任意请输入*): ";
	cin >> dest;
	if (dep[0] == '*')dep[0] = '\0';
	if (dest[0] == '*')dest[0] = '\0';

	Service::Flight::PrintFlights(dep.c_str(), dest.c_str());
}

void QueryTickets()
{
	string name, id;
	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入证件号: ";
	cin >> id;

	try
	{
		auto customer = new Service::Customer(name.c_str(), id.c_str());
		customer->PrintTickets();
		delete customer;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}

}

void QueryCustomers()
{
	string flightName;
	cout << "请输入航班名: ";
	cin >> flightName;

	try
	{
		auto flight = new Service::Flight(flightName.c_str());
		flight->PrintCustomers();
		delete flight;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}
}

void Order()
{
	string name, id, flightName;

	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入证件号: ";
	cin >> id;
	cout << "请输入航班名: ";
	cin >> flightName;

	try
	{
		auto customer = new Service::Customer(name.c_str(), id.c_str());
		customer->MakeOrder(flightName.c_str());
		delete customer;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}
}

void RemoveOrder()
{
	string name, id, flightName;

	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入证件号: ";
	cin >> id;
	cout << "请输入航班名: ";
	cin >> flightName;

	try
	{
		auto customer = new Service::Customer(name.c_str(), id.c_str());
		customer->DeleteOrder(flightName.c_str());
		delete customer;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}

}

void InsertFlight()
{
	string flightName, departure, destination;
	int maxCapacity, week, hour, minute;
	time_t time = 0;
	// 1970.1.1 -> Thursday
	time += 4 * 24 * 60 * 60;

	cout << "请输入航班名称: ";
	cin >> flightName;

	cout << "请输入出发站: ";
	cin >> departure;

	cout << "请输入终点站: ";
	cin >> destination;

	cout << "请输入最大容量: ";
	cin >> maxCapacity;

	cout << "请输入航班起飞星期: ";
	cin >> week;
	while (week > 7 || week < 1)
	{
		cout << "输入星期不合法，请输入1到7内整数: " << endl;
		cin >> week;
	}
	time += (week - 1) * 24 * 60 * 60;

	cout << "请输入航班起飞小时: ";
	cin >> hour;
	while (hour > 24 || week < 0)
	{
		cout << "输入小时不合法，请输入0到24内整数 " << endl;
		cin >> hour;
	}
	time += hour * 60 * 60;

	cout << "请输入航班起飞分钟: ";
	cin >> minute;
	while (minute > 60 || minute < 0)
	{
		cout << "输入分钟不合法，请输入0到60内整数 " << endl;
		cin >> minute;
	}
	time += minute * 60;

	try
	{
		auto flight = new Service::Flight(flightName.c_str());
		flight->AddFlight(departure.c_str(), destination.c_str(), maxCapacity, time);
		delete flight;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}

}

void DeleteFlight()
{
	string flightName;
	cout << "请输入航班名: " << endl;
	cin >> flightName;

	try
	{
		auto flight = new Service::Flight(flightName.c_str());
		flight->DeleteFlight();
		delete flight;
	}
	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}
}