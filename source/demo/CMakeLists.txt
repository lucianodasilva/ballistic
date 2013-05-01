cmake_minimum_required(VERSION 2.8)

project ( demo )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB demo_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_executable ( demo ${demo_source} )
target_link_libraries ( demo game engine glfw ${glfw_LIBRARIES})