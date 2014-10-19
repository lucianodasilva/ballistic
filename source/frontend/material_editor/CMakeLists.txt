cmake_minimum_required(VERSION 2.8)

project ( material_editor_controller )
# ----------------------------------------------------------------

if (build_ballistic_opengl3)

	file ( GLOB win_desktop_source
		${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
		${CMAKE_CURRENT_LIST_DIR}/include/*.h
		${CMAKE_CURRENT_LIST_DIR}/include/*.inl
		${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
	)

	include_directories (${CMAKE_CURRENT_LIST_DIR}/include)

	project ( material_editor_controller )
	add_library ( material_editor_controller SHARED ${win_desktop_source} )

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		find_library(GLUT_LIBRARY GLUT )
		mark_as_advanced (
			COCOA_LIBRARY
		    GLUT_LIBRARY
		)

		set (BALLISTIC_MAC_GL_LIB ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})
		target_link_libraries ( material_editor_controller base graphics_opengl ${BALLISTIC_MAC_GL_LIB} glew frontend)
	else ()
		target_link_libraries ( material_editor_controller base graphics_opengl ${BALLISTIC_GL_LIBRARIES} glew frontend)
	endif ()

	set_property (TARGET material_editor_controller PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	set_property (TARGET material_editor_controller PROPERTY FOLDER "frontend/material_editor")
endif ()

