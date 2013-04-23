cmake_minimum_required(VERSION 2.8)

project ( ballistic )
# ----------------------------------------------------------------

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( engine_dir 	${proj_dir}/engine )
set ( game_dir 		${proj_dir}/game )

set ( engine_dir 	${engine_dir} 	CACHE STRING "Path to Engine Library" )
set ( game_dir 		${game_dir} 	CACHE STRING "Path to Game Implementation" )

include ( ${engine_dir}/CMakeLists.txt )
include ( ${game_dir}/CMakeLists.txt )

# enable c++11
if (NOT CMAKE_DEFINED_COMPILER MATCHES NOMAD_MSVC)
	if (CMAKE_GENERATOR STREQUAL Xcode)
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -g -Wall")
	endif ()
endif ()

project ( ballistic )
