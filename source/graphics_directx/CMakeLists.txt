cmake_minimum_required(VERSION 2.8)

project ( graphics_directx )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB graphics_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

find_package (DirectX)
if (NOT DirectX_FOUND)
	message ( FATAL_ERROR "Unable to build DirectX device implementation")
endif ()

add_library ( graphics_directx STATIC ${graphics_source} )

target_link_libraries ( graphics_directx base graphics DirectX_LIBRARY )