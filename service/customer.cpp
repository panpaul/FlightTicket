//
// Created by panyuxuan on 2020/5/7.
//

#include "customer.h"
customer::customer()
= default;

customer::customer(char* name, char* id)
{
	int namelength = strlen(name);
	int idlength = strlen(id);
	if(namelength<=(CUSTOMER_NAME_MAX_SIZE/sizeof(char))&&(idlength<=(CUSTOMER_ID_MAX_SIZE/sizeof(id)))){
		strcpy(this->name, name);
		strcpy(this->id,id);
	}
	else{
		flag = true;
		std::cout<<"请检查您的名字与ID拼写，他们超过了正常长度，若无法解决请致电xxxxxxx"<<std::endl;
	}
}

customer::~customer()
= default;

void customer::InsertCustomer()
{
	db::Customer customerStruct{};
	strcpy(customerStruct.Name,this->name);
	strcpy(customerStruct.Id,this->id);
	engine->InsertCustomer(customerStruct);
}
void customer::QueryCustomer() {
	if(!flag)return ;
	db::Customer customerStruct{};
	cust.CustomerId =0;
	strcpy(cust.Name,name);
	strcpy(cust.Id,id);
	std::vector <db::Customer> temp1 = engine->QueryCustomer(customerStruct);
	db::Order wants;
	wants.OrderId = 0;
	wants.CustomerId = temp1[0].CustomerId;
	std::vector<db::Order> orderlist = engine->QueryOrder(wants);
	for(auto itra = orderlist.begin();itra != orderlist.end();itra++){
		db::Flight flightStruct{};
		flightStruct.FlightId = orderlist[itra].FlightId;
		std::vector<db::Flight> flightlist = engine.QueryFlight(flightStruct);
		std::cout<<"-------------------------"<<std::endl;
		std::cout<<"航班号"<<flightlist[0].FlightName<<std::endl;
		std::cout<<"始发地"<<flightlist[0].Departure<<std::endl;
		std::cout<<"目的地"<<flightlist[0].Destination<<std::endl;
		std::cout<<"-------------------------"<<std::endl;
	}
}

void customer::MakeOrder(char *flightname) {
	if(!flag)return ;
	int id = InsertCustomer();
	db::Customer customerStruct{};
	db::Flight flightStruct{};
	strcpy(flightStruct.FlightName,flightname);
	strcpy(customerStruct.Name,this->name);
	std::vector<db::Flight> flightlist = engine.QueryFlight(flightStruct);
	std::vector<db::Customer> customerlish = engine.QueryCustomer(customerStruct);
	db::Order orderStruct{};
	orderStruct.CustomerId = customerlist[0].CustomerId;
	orderStruct.FlightId = flightlist[0].FlightId;
	std::vector<db::Order> judge = engine.QueryOrde(orderStruct);
	if(judge.empty()){
		std::cout<<"抱歉，航空公司规定对于每次航班一人仅能购买一张票，请重试"<<std::endl;
		return ;
	}
	if(flightlist[0].Current==0){
		std::cout<<"抱歉，该航班票已经售完，请选择其他航班"<<std::endl;
	}
	else
	{
		orferStruct.SeatId = flightlist[0].Current+1;
		engine->InsertOrder(orderStruct);
		db::Flight newflightStruct{};
		newflightStruct.Current = flightlist[0].Current+1;
		newflightStruct.MaxCapacity = flightlist[0].MaxCapacity;
		newflightStruct.FlightId = flightlist[0].FlightId;
		strcpy(newflightStruct.FlightName,flightlist[0].FlightName);
		strcpy(newflightStruct.Departure,flightlist[0].Departure);
		strcpy(newflightStruct.Destination,flightlist[0].Destination);
		engine->UpdateFlight(newflightStruct);
	}

}

void customer::DeleteOrder(char *flightname){
	if(!falg)return ;
	db::Customer customerStruct{};
	db::Flight flightStruct{};
	strcpy(flightStruct.FlightName,flightname);
	strcpy(customerStruct.Name,this->name);
	std::vector<db::Flight> flightlist = engine.QueryFlight(flightStruct);
	std::vector<db::Customer> customerlish = engine.QueryCustomer(customerStruct);
	db::Order orderStruct{};
	orderStruct.CustomerId = customerlist[0].CustomerId;
	orderStruct.FlightId = flightlist[0].FlightId;
	std::vector<db::Order> orderlist = engine.QueryOrder(orderStruct);

	if(orderlist.empty){
		std::cout<<"抱歉，您并没有购买本次航班的票，请检查姓名及航班号的输入"<<endl;
		return ;
	}

	engine.DeleteOrder(orderlist[0].OrderId);

	db::Flight newflightStruct{};
	newflightStruct.Current = flightlist[0].Current-1;
	newflightStruct.MaxCapacity = flightlist[0].MaxCapacity;
	newflightStruct.FlightId = flightlist[0].FlightId;
	strcpy(newflightStruct.FlightName,flightlist[0].FlightName);
	strcpy(newflightStruct.Departure,flightlist[0].Departure);
	strcpy(newflightStruct.Destination,flightlist[0].Destination);
	engine->UpdateFlight(newflightStruct);

}

