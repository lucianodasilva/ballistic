#pragma once
#ifndef _ballistic_config_h_
#define _ballistic_config_h_

/*  cmake generated operating system definitions
*
*   BALLISTIC_LINUX for linux
*   BALLISTIC_WIN for Windows
*   BALLISTIC_SUNOS for solaris
*
*/
#   define BALLISTIC_WIN

/*  cmake generated compiler definition
*
*   BALLISTIC_GNUXX for gnu c++
*   BALLISTIC_GNUCC for gnu c
*   BALLISTIC_MSVC for Microsoft Visual C++
*
*/
#   define BALLISTIC_GNUCC

// cmake define int data types
#include <stdint.h>

typedef int8_t      int8;
typedef uint8_t     uint8;
typedef int16_t     int16;
typedef uint16_t    uint16;
typedef int32_t     int32;
typedef uint32_t    uint32;
typedef int64_t     int64;
typedef uint64_t    uint64;

typedef float		real;

/* cmake defined platform endianess
*
*   BALLISTIC_BIG_ENDIAN
*   BALLISTIC_LITTLE_ENDIAN
*/
#define BALLISTIC_LITTLE_ENDIAN

#endif
