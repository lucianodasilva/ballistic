cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(tinyxml2)

################################
# Add common source 
include_directories(${CMAKE_CURRENT_LIST_DIR}/.)

################################
# Add definitions

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

add_library(tinyxml2 STATIC ${CMAKE_CURRENT_LIST_DIR}/tinyxml2.cpp ${CMAKE_CURRENT_LIST_DIR}/tinyxml2.h)

set_property (TARGET tinyxml2 PROPERTY FOLDER "deps")