cmake_minimum_required(VERSION 2.8)

project ( model_viewer )
# ----------------------------------------------------------------

project (model_viewer_resources)

file ( GLOB resource_files 
	${CMAKE_CURRENT_LIST_DIR}/resources/*
) 

add_custom_target(
    model_viewer_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    	${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:model_viewer>/model_viewer_res
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

if (build_ballistic_opengl3)
	project ( model_viewer )
	add_executable ( model_viewer ${win_desktop_source} )

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		find_library(GLUT_LIBRARY GLUT )
		mark_as_advanced (
			COCOA_LIBRARY
		    GLUT_LIBRARY
		)

		set (BALLISTIC_MAC_GL_LIB ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})
		target_link_libraries ( model_viewer base graphics_opengl ${BALLISTIC_MAC_GL_LIB} glew frontend)
	else ()
		target_link_libraries ( model_viewer base graphics_opengl ${BALLISTIC_GL_LIBRARIES} glew frontend)
	endif ()

	

	set_property (TARGET model_viewer PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	set_property (TARGET model_viewer PROPERTY FOLDER "frontend/model_viewer")
	set_property (TARGET model_viewer_resources PROPERTY FOLDER "frontend/model_viewer")
endif ()

