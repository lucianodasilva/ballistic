cmake_minimum_required(VERSION 2.8)

if (ballistic_opengl)

	project ( graphics_opengl )
	# ----------------------------------------------------------------

	include (${proj_dir}/deps/glew/CMakeLists.txt)

	include_directories (
		${CMAKE_CURRENT_LIST_DIR}/include
	)

	file ( GLOB graphics_gl_source
		${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
		${CMAKE_CURRENT_LIST_DIR}/include/*.h
		${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
	)

	add_library ( graphics_opengl STATIC ${graphics_gl_source} )

	target_link_libraries ( graphics_opengl base graphics ${ballistic_gl_dependencies} glew )

	set_property (TARGET graphics_opengl PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	
	set ( ballistic_graphics_dependencies ${ballistic_graphics_dependencies} graphics_opengl ${ballistic_gl_dependencies} glew )

endif ()

