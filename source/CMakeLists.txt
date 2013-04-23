cmake_minimum_required(VERSION 2.8)

project ( ballistic )
# ----------------------------------------------------------------

# Load engine library and main projects
set ( proj_dir ${CMAKE_CURRENT_LIST_DIR} )

set ( engine_dir 	${proj_dir}/engine )
set ( game_dir 		${proj_dir}/game )

set ( engine_dir 	${engine_dir} 	CACHE STRING "Path to Engine Library" )
set ( game_dir 		${game_dir} 	CACHE STRING "Path to Game Implementation" )

include ( ${engine_dir}/CMakeLists.txt )
include ( ${game_dir}/CMakeLists.txt )

project ( ballistic )
