#include "flight.h"
flight::flight() = default;
flight::flight(char *flightname){
	int namelength = strlen(flightname);
	if(namelength <= FLIGHT_NAME_MAX_SIZE/sizeof(char)){
		strcpy(this->flightname,flightname);
	}
	else {
		flag = false;
		std::cout<<"非法操作，信息过长"<<std::endl;
	}
}
flight::flight(char *flightname, char *departure, char *destination,int maxcapacity) {
	int namelength = strlen(flightname);
	int departurelength = strlen(departure);
	int destinationlength = strlen(destination);
	if((namelength <= FLIGHT_NAME_MAX_SIZE/sizeof(char)&&(departurelength <= FLIGHT_DEPARTURE_MAX_SIZE/sizeof(char))&&(destinationlength<=FLIGHT_DESTINATION_MAX_SIZE/sizeof(destination))){
		strcpy(this->flightname,flightname);
		strcpy(this->departure,departure);
		strcpy(this->destination,destination);
		this->MaxCapacity = maxcapacity;

		InsertFlight();
	}
	else flag = false;
}
void flight::InsertFlight() {
	db::Flight flightStruct{};
	strcpy(flightStruct.FlightName,this->flightname);
	strcpy(flightStruct.Departure,this->departure);
	strcpy(flightStruct.Destination,this->destination);
	flightStruct.MaxCapacity = MaxCapacity;
	flightStruct.Current = 0;

	engin.InsertFlight(flightStruct);
}

void flight::DeleteFlight(){
	if(!flag)return;
	db::Flight flightStruct{};
	strcpy(flightStruct.FlightName,this->flightname);

	std::vector<db::Flight> flightlist = engin.QueryFlight(flightStruct);

	if(flightlist.empty()){
		std::cout<<"非法操作，无此航班，请检查航班号"<<std::endl;
		return
	}
	engine.DeleteFlight(flightlist[0].FlightId);
}

void flight::QueryFlightbyDestination(char *destination){
	if(!flag)return ;
	db::Flight flightStruct{};
	strcpy(flightStruct.Destination,destination);

	std::vector<db::Flight> list = engine.QueryFlight(flightStruct);
	if(list.empty()){
		std::cout<<"非法操作，无此航班，请检查航班号"<<std::endl;
		return
	}

	std::cout<<"-------------------------"<<std::endl;
	for(auto itra = list.begin();itra != list.end();i++){
		std::cout<<"航班号:"<<list[itra].FlightName<<std::endl;
		std::cout<<"始发站:"<<list[itra].Departure<<std::endl;
		std::cout<<"剩余座位:"<<list[itra].Current<<std::endl;
		std::cout<<"-------------------------"<<std::endl;
	}
}
void flight::QueryFlightbyFlightname(char *flightname) {
	if(!flag)return ;
	db::Flight flightStruct{};
	strcpy(flightStruct.FlightName,flightname);
	std::vector<db::Flight> flightlist = engine.QueryFlight(flightStruct);

	db::Order orderStruct{};
	orderStruct.FlightId = flightlist[0].FlightId;
	std::vector<db::Order> orderlist = engine.QueryOrder(orderStruct);


	std::cout<<"-------------------------"<<std::endl;
	for(auto itra = orderlist.begin();itra != orderlist.end();itra++){
		db::Customer customerStruct{};
		customerStruct.CustomerId = orderlist[itra].CustomerId;
		std::vector<db::Customer>customerlist = engine.QueryCustomer(customerStruct);
		std::cout<<"乘客姓名:"<<customerlist[0].Name<<std::endl;
		std::cout<<"ID:"<<customerlist[0].ID<<std::endl;
		std::cout<<"乘客ID:"<<orderlist[itra].CustomerId<<std::endl;
		std::cout<<"座位号:"<<orderlist[itra].SeatId<<std::endl;
		std::cout<<"-------------------------"<<std::endl;
	}
}