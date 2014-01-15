cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(glew)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

set (glew_dir ${CMAKE_CURRENT_LIST_DIR})

file ( GLOB glew_source
	${glew_dir}/src/*.c
	${glew_dir}/include/GL/*.h
)

add_library(glew STATIC ${glew_source})

if (APPLE)
	find_library(COCOA_LIBRARY Cocoa)
	find_library(GLUT_LIBRARY GLUT )
	find_library(OpenGL_LIBRARY OpenGL )

	mark_as_advanced (
		COCOA_LIBRARY
	    GLUT_LIBRARY
		OpenGL_LIBRARY
	)

	set (OGL_LIBRARIES ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
	
else ()
	find_package (OpenGL REQUIRED)
	set ( OGL_LIBRARIES ${OPENGL_LIBRARY})
endif ()

target_link_libraries ( glew ${BALLISTIC_GL_LIBRARIES})

set_property (TARGET glew PROPERTY FOLDER "deps")