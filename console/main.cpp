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
void QueryCustomer(); // db not support
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

	auto f = new flight();
	if (f->query(dest.c_str()))
	{
		cout << "查询到航班:" << endl;
		cout << "\t航班号: " << f->FlightId << endl;
		cout << "\t航班名: " << f->FlightName << endl;
		cout << "\t出发站: " << f->Departure << endl;
		cout << "\t终点站: " << f->Destination << endl;
		cout << "\t最大容量: " << f->MaxCapacity << endl;
		cout << "\t剩余座位: " << f->MaxCapacity - f->Current << endl;
	}
	else
	{
		cout << "未查询到相关信息" << endl;
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

void test()
{
	auto le = new db::linearEngine(".");
	le->InsertFlight(db::Flight{ 1, "hello", "dep1", "des1", 2, 1 });
	le->InsertFlight(db::Flight{ 2, "world", "dep2", "des2", 2, 1 });
	le->InsertFlight(db::Flight{ 3, "test", "dep3", "des3", 2, 1 });

	//cout << le->queryFlight(db::Flight{ 0, "hello", "", "", 1, 2 }).FlightName << endl;
	//cout << le->queryFlight(db::Flight{ 2, "", "", "", 1, 2 }).FlightName << endl;
	//cout << le->queryFlight(db::Flight{ 0, "", "", "des3", 0, 0 }).FlightName << endl;

	//cout << (le->queryFlight(db::Flight{}).FlightId == 0 ? "PASS" : "FAILED") << endl;
	//cout << (le->queryFlight(db::Flight{ 0, "1" }).FlightId == 0 ? "PASS" : "FAILED") << endl;
	//cout << (le->queryFlight(db::Flight{ 0, "", "1" }).FlightId == 0 ? "PASS" : "FAILED") << endl;

	cout << le->DeleteFlight(1) << endl;
	cout << (le->QueryFlight(db::Flight{ 1 }).FlightId == 0 ? "PASS" : "FAILED") << endl;

	auto temp = le->QueryFlight(db::Flight{ 2 });
	cout << temp.Current << endl;
	temp.Current = 2;
	le->UpdateFlight(temp);
	temp = le->QueryFlight(db::Flight{ 2 });
	cout << temp.Current << endl;

	delete le;
}