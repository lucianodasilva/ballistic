cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(glew)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

set (glew_dir ${CMAKE_CURRENT_LIST_DIR})

file ( GLOB glew_source
	${glew_dir}/src/*.c
	${glew_dir}/include/*.h
)

add_library(glew STATIC ${glew_source})

if (APPLE)
	include_directories (/System/Library/Frameworks)
	find_library ( OpenGL_LIBRARY OpenGL )
	mark_as_advanced ( 
			OpenGL_LIBRARY
	)

	set (opengl_dep ${OpenGL_LIBRARY})
	
else ()
	find_package (OpenGL REQUIRED)
	set ( opengl_dep ${OPENGL_LIBRARY})
endif ()

target_link_libraries ( glew ${opengl_dep})

set_property (TARGET glew PROPERTY FOLDER "deps")