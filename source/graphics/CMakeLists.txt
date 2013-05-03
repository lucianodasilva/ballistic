cmake_minimum_required(VERSION 2.8)

project ( graphics )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB graphics_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library ( graphics STATIC ${graphics_source} )

if (APPLE)
	include_directories (/System/Library/Frameworks)
	find_library ( OpenGL_LIBRARY OpenGL )
	mark_as_advanced ( 
			OpenGL_LIBRARY
	)
else ()
	find_package(OpenGL REQUIRED)
endif ()

target_link_libraries ( graphics engine glfw ${glfw_LIBRARIES} ${OpenGL_LIBRARY} )