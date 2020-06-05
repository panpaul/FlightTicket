//
// Created by panyuxuan on 2020/6/4.
//
#include <ranges>
#include <iostream>
#include <vector>
#include <cstring>

#include "model/linearEngine.h"
#include "model/model.h"

using namespace std;

int main()
{
	auto engine = new db::linearEngine(".");
	engine->InsertFlight(db::Flight{ 1, "name1", "dep1", "des1", 3, 1 });
	engine->InsertFlight(db::Flight{ 2, "name2", "dep2", "des2", 3, 1 });
	engine->InsertFlight(db::Flight{ 3, "name3", "dep3", "des3", 3, 1 });
	engine->InsertFlight(db::Flight{ 4, "name4", "dep4", "des4", 3, 1 });
	engine->InsertFlight(db::Flight{ 5, "name5", "dep2", "des5", 3, 1 });
	engine->InsertFlight(db::Flight{ 6, "name6", "dep2", "des6", 3, 1 });
	engine->InsertFlight(db::Flight{ 7, "name7", "dep2", "des7", 3, 1 });
	engine->InsertFlight(db::Flight{ 8, "name8", "dep8", "des8", 3, 1 });

	auto x = engine->QueryFlight(db::Flight{ 0, "", "dep2" });
	for (auto i : x)
	{
		cout << i.Destination << endl;
	}

	delete engine;

}