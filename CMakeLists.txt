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
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
ENDIF ()

project(FlightTicket)

add_executable(FlightTicket
        console/main.cpp
        model/definitions.h
        service/Customer.cpp service/Customer.h service/Flight.cpp service/Flight.h
        model/Base.cpp model/Base.h
        model/LinearEngine.cpp model/LinearEngine.h
        model/model.h
        service/service.cpp)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND "${CMAKE_CXX_COMPILER_VERSION}" GREATER_EQUAL "10")
    MESSAGE("Using ranges library provided by GNU")
ELSE ()
    MESSAGE("Using fallback support for ranges library")
    ADD_DEFINITIONS(-DUSING_FALLBACK_SUPPORT)
    find_package(range-v3 CONFIG REQUIRED)
    target_link_libraries(FlightTicket PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
ENDIF ()


project(test)
add_executable(test
        test/test.cpp
        model/definitions.h
        model/model.h
        model/Base.cpp model/Base.h
        model/LinearEngine.cpp model/LinearEngine.h
        )
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND "${CMAKE_CXX_COMPILER_VERSION}" GREATER_EQUAL "10")
    MESSAGE("Using ranges library provided by GNU")
ELSE ()
    MESSAGE("Using fallback support for ranges library")
    ADD_DEFINITIONS(-DUSING_FALLBACK_SUPPORT)
    find_package(range-v3 CONFIG REQUIRED)
    target_link_libraries(test PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
ENDIF ()

