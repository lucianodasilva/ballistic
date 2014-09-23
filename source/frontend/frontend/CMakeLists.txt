cmake_minimum_required(VERSION 2.8)

project ( frontend )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB frontend_lib_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

if (build_ballistic_opengl3)
	add_library ( frontend STATIC ${frontend_lib_source} )

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		find_library(GLUT_LIBRARY GLUT )
		mark_as_advanced (
			COCOA_LIBRARY
		    GLUT_LIBRARY
		)

		set (BALLISTIC_MAC_GL_LIB ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})
		target_link_libraries ( frontend base graphics_opengl ${BALLISTIC_MAC_GL_LIB} glew)
	else ()
		target_link_libraries ( frontend base graphics_opengl ${BALLISTIC_GL_LIBRARIES} glew)
	endif ()

	set_property (TARGET frontend PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	set_property (TARGET frontend PROPERTY FOLDER "frontend")

endif ()

