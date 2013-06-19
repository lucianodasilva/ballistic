cmake_minimum_required(VERSION 2.8)

project ( win_desktop )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB win_desktop_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

if (Ballistic_DXGraphics)
	project ( win_desktop_dx )
	add_executable ( win_desktop_dx ${win_desktop_source} )
	target_link_libraries ( win_desktop_dx base graphics_directx)

	set_property (TARGET win_desktop_dx PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_WIN_DX )

	set_property (TARGET win_desktop_dx PROPERTY FOLDER "frontend")
endif ()

if (Ballistic_OpenGLGraphics)
	project ( win_desktop_gl )
	add_executable ( win_desktop_gl ${win_desktop_source} )

	find_package ( OpenGL REQUIRED )


	target_link_libraries ( win_desktop_gl base graphics_opengl ${OPENGL_LIBRARY})

	set_property (TARGET win_desktop_gl PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_WIN_GL )

	set_property (TARGET win_desktop_gl PROPERTY FOLDER "frontend")
endif ()
