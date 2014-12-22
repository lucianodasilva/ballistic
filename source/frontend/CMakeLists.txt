cmake_minimum_required(VERSION 2.8)

project ( frontend )
# ----------------------------------------------------------------

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB frontend_lib_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/*.mm
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library ( frontend STATIC ${frontend_lib_source} )

if (APPLE)
	set(CMAKE_C_FLAGS "-x objective-c")
	set(CMAKE_CXX_FLAGS "-x objective-c++")

	find_library(COCOA_LIBRARY Cocoa)
	find_library(CORE_VIDEO_LIBRARY CoreVideo)

	mark_as_advanced (
		COCOA_LIBRARY,
		CORE_VIDEO_LIBRARY
	)

	set ( ballistic_frontend_dependencies ${COCOA_LIBRARY} ${CORE_VIDEO_LIBRARY} ${ballistic_graphics_dependencies} )
else ()
	set ( ballistic_frontend_dependencies ${ballistic_graphics_dependencies} )
endif ()

target_link_libraries ( frontend ${ballistic_frontend_dependencies})

set ( ballistic_frontend_dependencies frontend ${ballistic_frontend_dependencies} )