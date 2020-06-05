//
// Created by panyuxuan on 2020/5/7.
//

#include "../service/Customer.h"
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
		cout << endl;
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
	cout << "请输入终点站: ";
	cin >> dest;
	cout << endl;
	while (dest.length() >= FLIGHT_DESTINATION_MAX_SIZE/sizeof(char))
	{
		cout << "终点站长度过长，请重试: ";
		cin >> dest;
		cout<< endl;
	}
	char* destination;
	strcpy(destination,dest.c_str());
	flight flig;
	flig.QueryFlightbyDestination(destination);
}

void QueryCustomer()
{
	string name, id;

	cout << "请输入姓名: ";
	cin >> name;
	cout << endl;
	while (name.length() >= CUSTOMER_NAME_MAX_SIZE/sizeof(char))
	{
		cout << "姓名长度过长，请重试: ";
		cin >> name;
		cout << endl;
	}

	cout << "请输入证件号: ";
	cin >> id;
	cout << endl;
	while (id.length() >= CUSTOMER_ID_MAX_SIZE/sizeof(char))
	{
		cout << "证件长度过长，请重试: ";
		cin >> id;
		cout << endl;
	}

	char* Name ;
	strcpy(Name,name.c_str());
	char* Id ;
	strcpy(Id,id.c_str());
	customer cust(Name,Id);
	cust.QueryCustomer();
}

void Order()
{
	string name, id , flightname;

	cout << "请输入姓名: ";
	cin >> name;
	cout << endl;
	while (name.length() >= CUSTOMER_NAME_MAX_SIZE/sizeof(char))
	{
		cout << "姓名长度过长，请重试: ";
		cin >> name;
		cout << endl;
	}

	cout << "请输入证件号: ";
	cin >> id;
	cout << endl;
	while (id.length() >= CUSTOMER_ID_MAX_SIZE/sizeof(char))
	{
		cout << "证件长度过长，请重试: ";
		cin >> id;
		cout << endl;
	}

	cout << "请输入航班号: ";
	cin>>flightname;
	cout << endl;
	while(flightname.length()>=FLIGHT_NAME_MAX_SIZE/sizeof(char)){
		cout << "航班号过长，请重试: ";
		cin >> flightname;
		cout << endl;
	}


	char* Name ;
	strcpy(Name,name.c_str());
	char* Id ;
	strcpy(Id,id.c_str());
	char* Flightname;
	strcpy(Flightname,flightname.c_str());
	customer cust(Name,Id);
	cust.MakeOrder(Flightname);
}

void RemoveOrder()
{
	string name, id , flightname;

	cout << "请输入姓名: ";
	cin >> name;
	cout << endl;
	while (name.length() >= CUSTOMER_NAME_MAX_SIZE/sizeof(char))
	{
		cout << "姓名长度过长，请重试: ";
		cin >> name;
		cout << endl;
	}

	cout << "请输入证件号: ";
	cin >> id;
	cout << endl;
	while (id.length() >= CUSTOMER_ID_MAX_SIZE/sizeof(char))
	{
		cout << "证件长度过长，请重试: ";
		cin >> id;
		cout << endl;
	}

	cout << "请输入航班号: ";
	cin>>flightname;
	cout << endl;
	while(flightname.length()>=FLIGHT_NAME_MAX_SIZE/sizeof(char)){
		cout << "航班号过长，请重试: ";
		cin >> flightname;
		cout << endl;
	}


	char* Name ;
	strcpy(Name,name.c_str());
	char* Id ;
	strcpy(Id,id.c_str());
	char* Flightname;
	strcpy(Flightname,flightname.c_str());
	customer cust(Name,Id);
	cust.DeleteOrder(Flightname);


}

void InsertFlight()
{
	string flightname,departure,destination;
	int maxcapacity;

	cout << "请输入航班号: ";
	cin>>flightname;
	cout<<endl;
	while(flightname.length()>=FLIGHT_NAME_MAX_SIZE/sizeof(char)){
		cout << "航班号过长，请重试: ";
		cin >> flightname;
		cout<<endl;
	}


	cout << "请输入始发站: ";
	cin >> departure;
	cout<<endl;
	while (departure.length() >= FLIGHT_DEPARTURE_MAX_SIZE/sizeof(char))
	{
		cout << "始发站长度过长，请重试: ";
		cin >> departure;
		cout<<endl;
	}

	cout << "请输入终点站号: ";
	cin >> destination;
	cout<<endl;
	while (destination.length() >= FLIGHT_DESTINATION_MAX_SIZE/sizeof(char))
	{
		cout << "终点站长度过长，请重试: ";
		cin >> destination;
		cout<<endl;
	}

	cout<<"输入最大座位数：";
	cin>>maxcapacity;
	cout<<endl;

	char* Flightname;
	strcpy(Flightname,flightname.c_str());
	char* Departure ;
	strcpy(Departure, departure.c_str());
	char* Destination ;
	strcpy(Destination, destination.c_str());
	flight flig(Flightname,Departure,Destination,maxcapacity);
}

void DeleteFlight()
{
	string flightname;
	cout << "请输入航班号: " << endl;
	cin>>flightname;
	while(flightname.length()>=FLIGHT_NAME_MAX_SIZE/sizeof(char)){
		cout << "航班号过长，请重试: " << endl;
		cin >> flightname;
	}
	char* Flightname;
	strcpy(Flightname, flightname.c_str());

	flight flig(Flightname);
	flig.DeleteFlight();
}