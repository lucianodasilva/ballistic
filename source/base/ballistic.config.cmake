# setup operating system id ---------------------------
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set (
        BALLISTIC_OS_DEFINES
        "#define BALLISTIC_OS_WINDOWS 1"
    )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set (
        BALLISTIC_OS_DEFINES
        "#define BALLISTIC_OS_LINUX 1"
    )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (
        BALLISTIC_OS_DEFINES
        "#define BALLISTIC_OS_DARWIN 1"
    )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Sun")
    set (
        BALLISTIC_OS_DEFINES
        "#define BALLISTIC_OS_SUN 1"
    )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set (
        BALLISTIC_OS_DEFINES
        "#define BALLISTIC_OS_FREEBSD 1"
    )
endif ()
# -----------------------------------------------------
message ( STATUS ${CMAKE_CXX_COMPILER_ID})
# setup compiler id -----------------------------------
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set (BALLISTIC_COMPILER_TYPE "#define BALLISTIC_COMPILER_MSVC 1")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set (BALLISTIC_COMPILER_TYPE "#define BALLISTIC_COMPILER_CLANG 1")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set (BALLISTIC_COMPILER_TYPE "#define BALLISTIC_COMPILER_GNU 1")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "SunPro")
    set (BALLISTIC_COMPILER_TYPE "#define BALLISTIC_COMPILER_SUNPRO 1")
endif ()
# -----------------------------------------------------

# setup api type --------------------------------------
if (UNIX)
    set (
        BALLISTIC_API_TYPE "#define BALLISTIC_API_UNIX 1"
    )
elseif (WIN32)
    set (
        BALLISTIC_API_TYPE "#define BALLISTIC_API_WIN32 1"
    )
endif ()
# -----------------------------------------------------

# common include files --------------------------------
include (CheckIncludeFiles)

CHECK_INCLUDE_FILES (cstdint HAVE_CSTDINT)
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H_)

if (HAVE_STDINT_H_ OR HAVE_CSTDINT)
    
    if (HAVE_CSTDINT)
        set (BALLISTIC_COMMON_INCLUDES "#include <cstdint> ")
    else ()
        set (BALLISTIC_COMMON_INCLUDES "#include <stdint.h> ")
    endif ()
endif ()
# -----------------------------------------------------

# generate conf file ----------------------------------
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/ballistic.config.in ${CMAKE_CURRENT_LIST_DIR}/include/ballistic.config.h)
# -----------------------------------------------------
