cmake_minimum_required(VERSION 2.8)

project ( dev )
# ----------------------------------------------------------------

project (dev_resources)

file ( GLOB resource_files 
	${CMAKE_CURRENT_LIST_DIR}/resources/*
) 

add_custom_target(
    dev_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    	${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:dev>/resources
    SOURCES ${resource_files}
)

#add_custom_command(TARGET dev_gl_resources PRE_BUILD
#               COMMAND ${CMAKE_COMMAND} -E copy_directory
#                   ${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:dev_gl>/resources)

include_directories (
	${CMAKE_CURRENT_LIST_DIR}/include
)

file ( GLOB dev_source
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
	${CMAKE_CURRENT_LIST_DIR}/include/*.inl
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

project ( dev )
add_executable ( dev ${dev_source} )

target_link_libraries ( dev ${ballistic_frontend_dependencies} )

set_property (TARGET dev PROPERTY COMPILE_DEFINITIONS BALLISTIC_DESKTOP_GL )
set_property (TARGET dev PROPERTY FOLDER "demo/dev")
set_property (TARGET dev_resources PROPERTY FOLDER "demo/dev")
