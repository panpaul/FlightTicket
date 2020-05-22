cmake_minimum_required(VERSION 3.10)
project(FlightTicket)

set(CMAKE_CXX_STANDARD 14)

add_executable(FlightTicket main.cpp service/customer.cpp service/customer.h service/flight.cpp service/flight.h definitions.h database/hashTable.cpp database/hashTable.h database/database.cpp database/database.h database/linearEngine.cpp database/linearEngine.h database/struct.h)