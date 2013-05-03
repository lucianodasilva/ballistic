cmake_minimum_required(VERSION 2.8)

project ( ballistic )
# ----------------------------------------------------------------

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( deps_dir      ${proj_dir}/deps )
set ( engine_dir 	${proj_dir}/engine )
set ( graphics_dir 	${proj_dir}/graphics )
set ( game_dir 		${proj_dir}/game )
set ( demo_dir	    ${proj_dir}/demo )

set ( deps_dir      ${deps_dir}     CACHE STRING "Path to dependency containing folder" )
set ( graphics_dir 	${graphics_dir} CACHE STRING "Path to Graphics Library" )
set ( game_dir 		${game_dir} 	CACHE STRING "Path to Game Implementation" )
set ( demo_dir      ${demo_dir}     CACHE STRING "Path to Demo implementation" )

# include dependencies
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
# glfw
include ( ${deps_dir}/glfw/CMakeLists.txt )
set_property (TARGET glfw PROPERTY FOLDER "dependencies")

include ( ${deps_dir}/glm/CMakeLists.txt )
set_property (TARGET glm PROPERTY FOLDER "dependencies")

include ( ${engine_dir}/CMakeLists.txt )
include ( ${graphics_dir}/CMakeLists.txt )
include ( ${game_dir}/CMakeLists.txt )
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

project ( ballistic )
