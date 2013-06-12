cmake_minimum_required(VERSION 2.8)

project ( ballistic_graphics )
# ----------------------------------------------------------------
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( Ballistic_Base_Dir      ${proj_dir}/base )
set ( Ballistic_Graphics_Dir  ${proj_dir}/graphics )
set ( Ballistic_Demo_Dir      ${proj_dir}/demo )

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set ( Ballistic_DXGraphics TRUE CACHE BOOL "Build for DirectX 9.0")
endif ()

set ( Ballistic_Base_Dir      ${Ballistic_Base_Dir}     CACHE PATH "Path to Base Library" )
set ( Ballistic_Graphics_Dir  ${Ballistic_Graphics_Dir} CACHE PATH "Path to Graphics Library" )
set ( Ballistic_Demo_Dir      ${Ballistic_Demo_Dir}     CACHE PATH  "Path to Demo implementation" )

# --------- dependencies ----------
include (${proj_dir}/deps/tinyxml2/CMakeLists.txt )
set_property (TARGET tinyxml2 PROPERTY FOLDER "deps")

# --------- core projects ----------
include ( ${Ballistic_Base_Dir}/CMakeLists.txt )
include ( ${Ballistic_Graphics_Dir}/CMakeLists.txt )
include ( ${Ballistic_Demo_Dir}/CMakeLists.txt )

# --------- frontends ---------

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include ( ${proj_dir}/frontend/win_desktop/CMakeLists.txt )
	set_property (TARGET win_desktop PROPERTY FOLDER "frontend")
endif ()
# -----------------------------

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
