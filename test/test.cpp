#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "../model/linearEngine.h"

using namespace std;

void CleanUp()
{
	remove("./flight.data");
	remove("./customer.data");
	remove("./order.data");
}

void AssertTrue(bool x)
{
	if (x)return;
	cerr << "Error" << endl;
	exit(-1);
}

void FlightTest();
void CustomerTest();
void OrderTest();

int main()
{
	CleanUp();
	FlightTest();
	cout << "Flight Test PASSED" << endl;
}

void FlightTest()
{
	auto engine = new db::linearEngine(".");
	int status = 0;

	// Test Insertion
	status = engine->InsertFlight(db::Flight{ 1, "name1", "dep1", "des1", 3, 1 });
	AssertTrue(status > 0);
	status = engine->InsertFlight(db::Flight{ 2, "name2", "dep2", "des2", 3, 1 });
	AssertTrue(status > 0);
	status = engine->InsertFlight(db::Flight{ 3, "name3", "dep3", "des3", 3, 1 });
	AssertTrue(status > 0);
	status = engine->InsertFlight(db::Flight{ 4, "name4", "dep2", "des4", 3, 1 });
	AssertTrue(status > 0);

	// Test Duplication
	status = engine->InsertFlight(db::Flight{ 5, "name2", "dep2", "des5", 3, 1 });
	AssertTrue(status == -1);
	status = engine->InsertFlight(db::Flight{ 6, "name2", "dep2", "des6", 3, 1 });
	AssertTrue(status == -1);
	status = engine->InsertFlight(db::Flight{ 7, "name2", "dep2", "des7", 3, 1 });
	AssertTrue(status == -1);

	// Test Query
	auto vec = engine->QueryFlight(db::Flight{ 0, "", "dep2" });
	AssertTrue(vec.size() == 2);

	delete engine;

	// Test Storage
	engine = new db::linearEngine(".");
	vec = engine->QueryFlight(db::Flight{ 1 });
	AssertTrue(vec.size() == 1);

	delete engine;
}