#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "../model/LinearEngine.h"

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
	CleanUp();

	CustomerTest();
	cout << "Customer Test PASSED" << endl;
	CleanUp();

	OrderTest();
	cout << "Order Test PASSED" << endl;
	CleanUp();
}

void FlightTest()
{
	auto engine = new db::LinearEngine(".");
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

	// Test Delete
	status = engine->DeleteFlight(4);
	AssertTrue(status);
	vec = engine->QueryFlight(db::Flight{ 0, "name4" });
	AssertTrue(vec.empty());

	// Test Storage
	delete engine;

	engine = new db::LinearEngine(".");
	vec = engine->QueryFlight(db::Flight{ 1 });
	AssertTrue(vec.size() == 1);

	delete engine;
}

void CustomerTest()
{
	auto engine = new db::LinearEngine(".");
	int status = 0;

	// Test Insertion
	status = engine->InsertCustomer(db::Customer{ 1, "name1", "id1" });
	AssertTrue(status > 0);
	status = engine->InsertCustomer(db::Customer{ 2, "name2", "id2" });
	AssertTrue(status > 0);
	status = engine->InsertCustomer(db::Customer{ 3, "name3", "id3" });
	AssertTrue(status > 0);
	status = engine->InsertCustomer(db::Customer{ 4, "name4", "id4" });
	AssertTrue(status > 0);

	// Test Duplication
	status = engine->InsertCustomer(db::Customer{ 2, "name2", "id2" });
	AssertTrue(status == -1);
	status = engine->InsertCustomer(db::Customer{ 5, "name2", "id5" });
	AssertTrue(status > 0);

	// Test Query
	auto vec = engine->QueryCustomer(db::Customer{ 0, "name2" });
	AssertTrue(vec.size() == 2);

	// Test Delete
	status = engine->DeleteCustomer(3);
	AssertTrue(status);
	vec = engine->QueryCustomer(db::Customer{ 0, "", "id3" });
	AssertTrue(vec.empty());

	// Test Storage
	delete engine;

	engine = new db::LinearEngine(".");
	vec = engine->QueryCustomer(db::Customer{ 1 });
	AssertTrue(vec.size() == 1);

	delete engine;
}

void OrderTest()
{
	auto engine = new db::LinearEngine(".");
	int status = 0;

	// Test Insertion
	status = engine->InsertOrder(db::Order{ 1, 1, 1, 1 });
	AssertTrue(status > 0);
	status = engine->InsertOrder(db::Order{ 1, 1, 2, 1 });
	AssertTrue(status > 0);
	status = engine->InsertOrder(db::Order{ 1, 2, 1, 2 });
	AssertTrue(status > 0);
	status = engine->InsertOrder(db::Order{ 1, 2, 2, 2 });
	AssertTrue(status > 0);

	// Test Duplication
	status = engine->InsertOrder(db::Order{ 1, 1, 2, 1 });
	AssertTrue(status == -1);
	status = engine->InsertOrder(db::Order{ 1, 2, 2, 2 });
	AssertTrue(status == -1);

	// Test Query
	auto vec = engine->QueryOrder(db::Order{ 0, 1 });
	AssertTrue(vec.size() == 2);

	// Test Delete
	status = engine->DeleteOrder(1);
	AssertTrue(status);
	vec = engine->QueryOrder(db::Order{ 0, 1, 1 });
	AssertTrue(vec.empty());

	// Test Storage
	delete engine;

	engine = new db::LinearEngine(".");
	vec = engine->QueryOrder(db::Order{ 0, 2 });
	AssertTrue(vec.size() == 2);

	delete engine;
}