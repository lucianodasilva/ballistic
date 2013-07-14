cmake_minimum_required(VERSION 2.8)

project ( dev_frontend )
# ----------------------------------------------------------------

project (frontend_resources)

file ( GLOB resource_files 
	${CMAKE_CURRENT_LIST_DIR}/resources/*
) 

add_custom_target(
    frontend_resources
    SOURCES ${resource_files}
)

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB win_desktop_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

if (Ballistic_DXGraphics )
	project ( dev_dx )
	add_executable ( dev_dx ${win_desktop_source} )
	target_link_libraries ( dev_dx base graphics_directx)

	set_property (TARGET dev_dx PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_DX )
	set_property (TARGET dev_dx PROPERTY FOLDER "frontend")

	add_custom_command(TARGET dev_dx PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:dev_dx>/resources)
endif ()

if (Ballistic_OpenGLGraphics)
	project ( dev_gl )
	add_executable ( dev_gl ${win_desktop_source} )

	add_custom_command(TARGET dev_gl PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:dev_gl>/resources)

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		find_library(GLUT_LIBRARY GLUT )
		mark_as_advanced (
			COCOA_LIBRARY
		    GLUT_LIBRARY
		)

		set (BALLISTIC_MAC_GL_LIB ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})
		target_link_libraries ( dev_gl base graphics_opengl ${BALLISTIC_MAC_GL_LIB} glew)
	else ()
		target_link_libraries ( dev_gl base graphics_opengl ${BALLISTIC_GL_LIBRARIES} glew)
	endif ()

	

	set_property (TARGET dev_gl PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	set_property (TARGET dev_gl PROPERTY FOLDER "frontend")
endif ()

