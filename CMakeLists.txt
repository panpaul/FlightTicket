cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(Doxygen)
OPTION(BUILD_DOCUMENTATION "Create the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

IF (BUILD_DOCUMENTATION)
    IF (NOT DOXYGEN_FOUND)
        MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation.")
    ENDIF ()

    SET(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)

    ADD_CUSTOM_TARGET(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
ENDIF ()


project(FlightTicket)
add_executable(FlightTicket
        console/main.cpp
        model/definitions.h
        service/service.h service/customer.cpp service/customer.h service/flight.cpp service/flight.h
        model/hashTable.cpp model/hashTable.h
        model/base.cpp model/base.h
        model/linearEngine.cpp model/linearEngine.h
        model/model.h
        )

project(debug)
add_executable(debug
        debug.cpp
        model/definitions.h
        model/model.h
        model/base.cpp model/base.h
        model/linearEngine.cpp model/linearEngine.h
        )

project(instant)
add_executable(instant
        debug.cpp
        model/model.h
        model/definitions.h
        )