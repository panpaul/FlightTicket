//
// Created by panyuxuan on 2020/5/7.
//

#include "../service/customer.h"
#include "../service/flight.h"
#include <iostream>

using namespace std;

void print()
{
	cout << "请选择功能：" << endl;
	cout << "\t0)退出" << endl;
	cout << "\t1)查询航班" << endl;
	cout << "\t2)浏览乘客信息" << endl;
	cout << "\t3)乘客订票" << endl;
	cout << "\t4)乘客退票" << endl;
	cout << "\t5)增加航班" << endl;
	cout << "\t6)删除航班" << endl;
	cout << "请输入您的选择: ";
}

void QueryFlight();
void QueryCustomer();
void Order();
void RemoveOrder();
void InsertFlight();
void DeleteFlight();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	while (true)
	{
		unsigned choices;
		print();
		cin >> choices;
		if (choices == 0)break;
		if (choices > 6)
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
			QueryCustomer();
			break;
		case 3:
			Order();
			break;
		case 4:
			RemoveOrder();
			break;
		case 5:
			InsertFlight();
			break;
		case 6:
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
	string dest;
	cout << "请输入终点站: " << endl;
	cin >> dest;
	while (dest.length() >= FLIGHT_DESTINATION_MAX_SIZE)
	{
		cout << "终点站长度过长，请重试: " << endl;
		cin >> dest;
	}

}

void QueryCustomer()
{

}

void Order()
{
	string name, id;
	int flight;

	cout << "请输入姓名: " << endl;
	cin >> name;
	while (name.length() >= CUSTOMER_NAME_MAX_SIZE)
	{
		cout << "姓名长度过长，请重试: " << endl;
		cin >> name;
	}

	cout << "请输入证件号: " << endl;
	cin >> id;
	while (id.length() >= CUSTOMER_ID_MAX_SIZE)
	{
		cout << "证件长度过长，请重试: " << endl;
		cin >> id;
	}

	cout << "请输入航班号: " << endl;
	cin >> flight;

}

void RemoveOrder()
{
}

void InsertFlight()
{
}

void DeleteFlight()
{
}