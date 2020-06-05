#ifndef FLIGHTTICKET_SERVICE_FLIGHT_H_
#define FLIGHTTICKET_SERVICE_FLIGHT_H_

#include"../model/linearEngine.h"
#include"service.h"
#include<cstring>
#include<iostream>
#include"../model/definitions.h"
class flight
{
 public:
	flight();
	flight(char *flightname);
	flight(char* flightname,char* departure,char* destination,int maxcapacity);
	~flight();
	void InsertFlight();
	void QueryFlightbyDestination(char *destination);
	void QueryFlightbyFlightname(char *flightname);
	void DeleteFlight();

 private:
	bool flag = true;
	char destination[FLIGHT_DESTINATION_MAX_SIZE/sizeof(char)];
	char departure[FLIGHT_DEPARTURE_MAX_SIZE/sizeof(char)];
	char flightname[FLIGHT_NAME_MAX_SIZE/sizeof(char)];
	int MaxCapacity;
};

#endif //FLIGHTTICKET_SERVICE_FLIGHT_H_
