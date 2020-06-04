//
// Created by panyuxuan on 2020/6/4.
//
#include <ranges>
#include <iostream>
#include <vector>

#include "model/model.h"

using namespace std;

int main()
{
	vector<db::Flight> vec;
	vec.push_back(db::Flight{ 1, "name1", "dep1", "des1", 3, 0 });
	vec.push_back(db::Flight{ 2, "name2", "dep2", "des2", 3, 1 });
	vec.push_back(db::Flight{ 3, "name3", "dep3", "des3", 3, 2 });

	auto filter = [](db::Flight f)
	{
	  return f.FlightId == 1;
	};

	for (auto i : vec | std::views::filter(filter))
	{
		cout << i.FlightName << endl;
	}
}