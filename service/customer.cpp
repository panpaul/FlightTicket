//
// Created by panyuxuan on 2020/5/7.
//

#include "customer.h"
int customer::counter = 0;
customer::customer()
= default;

customer::customer(char* name, char* id)
{
	strcpy(this->name, name);
	strcpy(this->id,id);
	InsertCustomer();
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
	return QueryCustomer(this->name,this->id);
}
/*
 * 如果要使用登录式的交互方式用这种方式
 */
void customer::QueryCustomer(char* name , char* id) {
	db::Customer cust ;
	cust.CustomerId =0;
	strcpy(cust.Name,name);
	strcpy(cust.Id,id);
	std::vector <db::Customer> temp1 = engine->QueryCustomer(cust);
	db::Order wants;
	wants.OrderId = 0;
	wants.CustomerId = temp1[1].CustomerId;
	std::vector<db::Order> list = engine->QueryOrder(wants);
	for(auto itra = list.begin()+1;itra != list.end();itra++){
		/*TODO
		 *  打印航班信息
		 */
	}
}
/*
 * 如果直接输入查询用这个
 */