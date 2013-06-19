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

include_directories ( /System/Library/Frameworks )
find_library(COCOA_LIBRARY Cocoa)
find_library(GLUT_LIBRARY GLUT )
find_library(OpenGL_LIBRARY OpenGL )
mark_as_advanced (
	COCOA_LIBRARY
    GLUT_LIBRARY
    OpenGL_LIBRARY
)

set (opengl_dep ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})

add_executable ( mac_desktop ${mac_desktop_source} )
target_link_libraries ( mac_desktop base graphics_opengl ${opengl_dep})

set_property (TARGET mac_desktop PROPERTY FOLDER "frontend")