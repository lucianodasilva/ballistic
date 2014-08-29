cmake_minimum_required(VERSION 2.8)

project ( perf_test )
# ----------------------------------------------------------------

project (perf_test_resources)

file ( GLOB resource_files 
	${CMAKE_CURRENT_LIST_DIR}/resources/*
) 

add_custom_target(
    perf_test_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    	${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:perf_test>/resources
    SOURCES ${resource_files}
)

#add_custom_command(TARGET dev_gl_resources PRE_BUILD
#               COMMAND ${CMAKE_COMMAND} -E copy_directory
#                   ${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:dev_gl>/resources)

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
	project ( perf_test )
	add_executable ( perf_test ${win_desktop_source} )

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		find_library(GLUT_LIBRARY GLUT )
		mark_as_advanced (
			COCOA_LIBRARY
		    GLUT_LIBRARY
		)

		set (BALLISTIC_MAC_GL_LIB ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})
		target_link_libraries ( perf_test base graphics_opengl ${BALLISTIC_MAC_GL_LIB} glew)
	else ()
		target_link_libraries ( perf_test base graphics_opengl ${BALLISTIC_GL_LIBRARIES} glew)
	endif ()

	set_property (TARGET perf_test PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
	set_property (TARGET perf_test PROPERTY FOLDER "frontend")
	set_property (TARGET perf_test_resources PROPERTY FOLDER "frontend")
endif ()

