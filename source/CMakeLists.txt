cmake_minimum_required(VERSION 2.8)

# set module path -------------------------------------
include (${CMAKE_CURRENT_LIST_DIR}/cmake/git.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/cmake/system.cmake)
# -----------------------------------------------------

project ( ballistic )
# ----------------------------------------------------------------
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# calculate current code version ----------------------
git_revision (HEAD ${CMAKE_CURRENT_LIST_DIR}/.. BALLISTIC_REVISION_COUNT)
git_revision_hash (HEAD ${CMAKE_CURRENT_LIST_DIR}/.. BALLISTIC_REVISION)

message (STATUS "ballistic version: ${BALLISTIC_REVISION_COUNT}.${BALLISTIC_REVISION}")

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( ballistic_base_dir       			${proj_dir}/base )
set ( ballistic_graphics_dir   			${proj_dir}/graphics )
set ( ballistic_graphics_opengl3_dir	${proj_dir}/graphics_opengl )

set ( build_ballistic_opengl3 TRUE CACHE BOOL "Build for OpenGL 3")

# library source code path settings
set ( ballistic_base_dir      ${ballistic_base_dir}     CACHE PATH "Path to Base Library" )
set ( ballistic_graphics_dir  ${ballistic_graphics_dir} CACHE PATH "Path to Graphics Library" )

set ( ballistic_graphics_opengl3_dir ${ballistic_graphics_opengl3_dir} CACHE PATH "Path to OpenGL device implementation")

# --------- dependencies ----------
include (${proj_dir}/deps/tinyxml2/CMakeLists.txt )
include (${proj_dir}/deps/glew/CMakeLists.txt)
include (${proj_dir}/deps/zlib/CMakeLists.txt)
include (${proj_dir}/deps/lpng/CMakeLists.txt)

# --------- core projects ----------
include ( ${ballistic_base_dir}/CMakeLists.txt )

include ( ${ballistic_graphics_dir}/CMakeLists.txt )

if ( build_ballistic_opengl3 )
	include (${ballistic_graphics_opengl3_dir}/CMakeLists.txt)
endif()

# --------- frontends ---------

# development frontend
include ( ${proj_dir}/frontend/frontend/CMakeLists.txt )
include ( ${proj_dir}/frontend/dev_frontend/CMakeLists.txt )
include ( ${proj_dir}/frontend/perf_test/CMakeLists.txt )
include ( ${proj_dir}/frontend/model_viewer/CMakeLists.txt )

# -----------------------------

# enable c++11
if (NOT ${CMAKE_CXX_COMPILER_ID} EQUAL "MSVC")
	if (CMAKE_GENERATOR STREQUAL Xcode)
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -g -Wall")
	endif ()
endif ()

project ( ballistic )
