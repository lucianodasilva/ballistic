cmake_minimum_required(VERSION 2.8)

project ( gl_4_transform )
# ----------------------------------------------------------------
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

# --------- dependencies ----------
include (${proj_dir}/glew/CMakeLists.txt)
include (${proj_dir}/glm/CMakeLists.txt)

project ( gl_4_transform )
# ----------------------------------------------------------------

include_directories (
	${proj_dir}/include
)

file ( GLOB gl_source
	${proj_dir}/*.cpp
	${proj_dir}/*.h
	${proj_dir}/*.hpp
)

add_executable ( gl_4_transform  ${gl_source} )

target_link_libraries ( gl_4_transform ${OGL_LIBRARIES} glew)

# enable c++11
if (NOT ${CMAKE_CXX_COMPILER_ID} EQUAL "MSVC")
	if (CMAKE_GENERATOR STREQUAL Xcode)
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
		set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -g -Wall")
	endif ()
endif ()

project ( gl_4_transform )
