cmake_minimum_required(VERSION 2.8)

project ( ballistic_graphics )
# ----------------------------------------------------------------

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( base_dir      ${proj_dir}/base )
set ( graphics_dir 	${proj_dir}/graphics )
set ( demo_dir	    ${proj_dir}/demo )

set ( base_dir 		${base_dir} 	CACHE STRING "Path to Base Library" )
set ( graphics_dir 	${graphics_dir} CACHE STRING "Path to Graphics Library" )
set ( demo_dir      ${demo_dir}     CACHE STRING "Path to Demo implementation" )

include ( ${base_dir}/CMakeLists.txt )
include ( ${graphics_dir}/CMakeLists.txt )
include ( ${demo_dir}/CMakeLists.txt )

# enable c++11
if (NOT CMAKE_DEFINED_COMPILER MATCHES BALLISTIC_MSVC)
	if (CMAKE_GENERATOR STREQUAL Xcode)
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -g -Wall")
	endif ()
endif ()

project ( ballistic_graphics )
