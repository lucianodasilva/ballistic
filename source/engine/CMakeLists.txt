cmake_minimum_required(VERSION 2.8)

project ( engine )
# ----------------------------------------------------------------

include ( ${CMAKE_CURRENT_LIST_DIR}/CMake.Generate.txt )

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB engine_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library ( engine SHARED ${engine_source} )