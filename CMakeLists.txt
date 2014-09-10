################################################################
# Project GUACAMOLE_MATERIALS
################################################################

PROJECT(GUACAMOLE_MATERIALS CXX)

cmake_minimum_required(VERSION 2.8.0)

find_package(PkgConfig)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

################################################################
# Configure and find libraries
################################################################

find_package(Json REQUIRED)

set(BOOST_ROOT "/opt/boost/boost_1_55_0")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS thread system filesystem)

set(LIBS
  ${Boost_LIBRARIES}
  ${JSON_LIBRARIES}
)
link_libraries(${LIBS})

set(LIB_PATHS
  ${Boost_LIBRARY_DIRS}
  ${JSON_LIBRARY_DIRS}
)
link_directories(${LIB_PATHS})

set(INCLUDE_PATHS
  ${Boost_INCLUDE_DIRS}
  ${JSON_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
include_directories(SYSTEM ${INCLUDE_PATHS})

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "release")
endif()

IF(CMAKE_BUILD_TYPE MATCHES "release")
  set(CMAKE_CXX_FLAGS "-s -Ofast --std=c++0x")
ELSE(CMAKE_BUILD_TYPE MATCHES "release")
  set(CMAKE_CXX_FLAGS "-g -Wall --std=c++0x")
ENDIF(CMAKE_BUILD_TYPE MATCHES "release")

################################################################
# Create executable
################################################################

file(GLOB_RECURSE EXAMPLE_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c src/*.cpp)

SET(_EXE_NAME test)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE( ${_EXE_NAME}
    ${EXAMPLE_SRC}
)

################################################################
# Summary
################################################################

message( "" )
message( "Summary:" )
message( " build type: ${CMAKE_BUILD_TYPE}" )
message( "" )
message( " boost:" )
message( "   library: ${Boost_LIBRARIES}" )
message( "   include: ${Boost_INCLUDE_DIRS}" )
message( "" )
message( " json:" )
message( "   library: ${JSON_LIBRARIES}" )
message( "   library path: ${JSON_LIBRARY_DIRS}" )
message( "   include: ${JSON_INCLUDE_DIRS}" )
message( "" )
