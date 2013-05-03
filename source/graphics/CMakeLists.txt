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

find_package(OpenGL REQUIRED)

target_link_libraries ( graphics engine ${OPENGL_gl_LIBRARY} )