# CMakeLists.txt

# Copyright (C) 2007-2013 Glenn Randers-Pehrson

# This code is released under the libpng license.
# For conditions of distribution and use, see the disclaimer
# and license in png.h

cmake_minimum_required(VERSION 2.8)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

set(PNGLIB_MAJOR 1)
set(PNGLIB_MINOR 6)
set(PNGLIB_RELEASE 9)
set(PNGLIB_NAME libpng${PNGLIB_MAJOR}${PNGLIB_MINOR})
set(PNGLIB_VERSION ${PNGLIB_MAJOR}.${PNGLIB_MINOR}.${PNGLIB_RELEASE})

if(NOT WIN32)
  find_library(M_LIBRARY
    NAMES m
    PATHS /usr/lib /usr/local/lib
  )
  if(NOT M_LIBRARY)
    message(STATUS
      "math library 'libm' not found - floating point support disabled")
  endif()
else()
  # not needed on windows
  set(M_LIBRARY "")
endif()

# Use the prebuilt pnglibconf.h file from the scripts folder
# TODO: fix this by building with awk; without this no cmake build can be
# configured directly (to do so indirectly use your local awk to build a
# pnglibconf.h in the build directory.)
configure_file(${CMAKE_CURRENT_LIST_DIR}/scripts/pnglibconf.h.prebuilt
               ${CMAKE_CURRENT_LIST_DIR}/pnglibconf.h)

include_directories(${CMAKE_CURRENT_LIST_DIR})

# OUR SOURCES
set(libpng_public_hdrs
  ${CMAKE_CURRENT_LIST_DIR}/png.h
  ${CMAKE_CURRENT_LIST_DIR}/pngconf.h
  ${CMAKE_CURRENT_LIST_DIR}/pnglibconf.h
)
set(libpng_sources
  ${libpng_public_hdrs}
 ${CMAKE_CURRENT_LIST_DIR}/pngdebug.h
  ${CMAKE_CURRENT_LIST_DIR}/pnginfo.h
  ${CMAKE_CURRENT_LIST_DIR}/pngpriv.h
  ${CMAKE_CURRENT_LIST_DIR}/pngstruct.h
  ${CMAKE_CURRENT_LIST_DIR}/png.c
  ${CMAKE_CURRENT_LIST_DIR}/pngerror.c
  ${CMAKE_CURRENT_LIST_DIR}/pngget.c
  ${CMAKE_CURRENT_LIST_DIR}/pngmem.c
  ${CMAKE_CURRENT_LIST_DIR}/pngpread.c
  ${CMAKE_CURRENT_LIST_DIR}/pngread.c
  ${CMAKE_CURRENT_LIST_DIR}/pngrio.c
  ${CMAKE_CURRENT_LIST_DIR}/pngrtran.c
  ${CMAKE_CURRENT_LIST_DIR}/pngrutil.c
  ${CMAKE_CURRENT_LIST_DIR}/pngset.c
  ${CMAKE_CURRENT_LIST_DIR}/pngtrans.c
  ${CMAKE_CURRENT_LIST_DIR}/pngwio.c
  ${CMAKE_CURRENT_LIST_DIR}/pngwrite.c
  ${CMAKE_CURRENT_LIST_DIR}/pngwtran.c
  ${CMAKE_CURRENT_LIST_DIR}/pngwutil.c
)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif(MSVC)

add_library(png STATIC ${libpng_sources})
target_link_libraries(png zlib)

set_property (TARGET png PROPERTY FOLDER "deps")