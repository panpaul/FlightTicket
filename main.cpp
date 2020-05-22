//
// Created by panyuxuan on 2020/5/7.
//

#include "service/customer.h"
#include "database/hashTable.h"
#include "database/linearEngine.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	auto le = new db::linearEngine(".");
	le->insertFlight(db::Flight{ 1, "hello", "dep1", "des1", 2, 1 });
	le->insertFlight(db::Flight{ 2, "world", "dep2", "des2", 2, 1 });
	le->insertFlight(db::Flight{ 3, "test", "dep3", "des3", 2, 1 });

	cout << le->queryFlight(db::Flight{ 0, "hello", "", "", 1, 2 }).FlightName << endl;
	cout << le->queryFlight(db::Flight{ 2, "", "", "", 1, 2 }).FlightName << endl;
	cout << le->queryFlight(db::Flight{ 0, "", "", "des3", 0, 0 }).FlightName << endl;

	cout << le->queryFlight(db::Flight{}).FlightName << endl;
	cout << le->queryFlight(db::Flight{ 0, "1" }).FlightName << endl;
	cout << le->queryFlight(db::Flight{ 0, "", "1" }).FlightName << endl;

	delete le;

	return 0;
}