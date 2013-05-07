cmake_minimum_required(VERSION 2.8)

project ( glew )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB glew_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.c
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library ( glew STATIC ${glew_source} )

set_property ( 
	TARGET glew
	APPEND
	PROPERTY COMPILE_DEFINITIONS GLEW_STATIC
)
#target_link_libraries ( glew )