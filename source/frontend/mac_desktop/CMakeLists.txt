cmake_minimum_required(VERSION 2.8)

project ( mac_desktop )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB mac_desktop_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

find_library(COCOA_LIBRARY Cocoa)
find_library(GLUT_LIBRARY GLUT )
mark_as_advanced (
	COCOA_LIBRARY
    GLUT_LIBRARY
)

set (BALLISTIC_MAC_GL ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${BALLISTIC_GL_LIBRARIES})

add_executable ( mac_desktop ${mac_desktop_source} )
target_link_libraries ( mac_desktop base graphics_opengl ${BALLISTIC_MAC_GL})

set_property (TARGET mac_desktop PROPERTY FOLDER "frontend")