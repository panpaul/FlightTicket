/**
 * @file linearEngine.cpp
 * @brief the basic storage engine used in database
 * @details file I/O, basic query with O(n)
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#include <fstream>
#include <iostream>
#include <cstring>
#include "linearEngine.h"

db::linearEngine::linearEngine(const std::string& path)
{
	basePath = path;
	flightVec.push_back(Flight{ 1, "hello1", "dep1", "des1", 1, 1 });
	flightVec.push_back(Flight{ 2, "hello2", "dep2", "des2", 2, 2 });
	flightVec.push_back(Flight{ 3, "hello3", "dep3", "des3", 3, 3 });
	flightVec.push_back(Flight{ 4, "hello4", "dep4", "des4", 4, 4 });
}

db::linearEngine::~linearEngine()
{
	saveFlight();
	flightVec.clear();
	loadFlight();
	for (auto& i : flightVec)
	{
		std::cout << i.FlightName << std::endl;
	}
}

void db::linearEngine::loadFlight()
{
	char data[FLIGHT_SIZE + 1];
	struct Flight flight{};
	std::ifstream ifs(basePath + "/flight.data", std::ios_base::in | std::ios_base::binary);
	if (!ifs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << basePath + "/flight.data" << std::endl;
		return;
	}

	while (ifs.read(data, FLIGHT_SIZE))
	{
		int cnt = 0;
		memcpy(&flight.FlightId, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&flight.FlightName, data + cnt, FLIGHT_NAME_MAX_SIZE);
		cnt += FLIGHT_NAME_MAX_SIZE;
		memcpy(&flight.Departure, data + cnt, FLIGHT_DEPARTURE_MAX_SIZE);
		cnt += FLIGHT_DEPARTURE_MAX_SIZE;
		memcpy(&flight.Destination, data + cnt, FLIGHT_DESTINATION_MAX_SIZE);
		cnt += FLIGHT_DESTINATION_MAX_SIZE;
		memcpy(&flight.MaxCapacity, data + cnt, sizeof(int));
		cnt += sizeof(int);
		memcpy(&flight.Current, data + cnt, sizeof(int));

		flightVec.push_back(flight);
	}

	ifs.close();
}

void db::linearEngine::saveFlight()
{
	std::ofstream ofs(basePath + "/flight.data",
		std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	if (!ofs.is_open())
	{
		// failed to open
		std::cerr << "Failed to open " << basePath + "/flight.data" << std::endl;
		return;
	}

	for (auto& i : flightVec)
	{
		ofs.write(reinterpret_cast<const char*>(&i), sizeof(Flight));
		//ofs << "\n";
	}

	ofs.close();
}
