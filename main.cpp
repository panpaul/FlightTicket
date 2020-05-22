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

	return 0;
}