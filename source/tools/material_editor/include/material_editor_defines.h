#pragma once
#ifndef _material_editor_defines_h_
#define _material_editor_defines_h_

#include <ballistic.base.h>

#ifdef BALLISTIC_API_WIN32

#	ifdef MATERIAL_EDITOR_EXPORT
#		define EXPORT extern "C" __declspec (dllimport)
#	else
#		define EXPORT extern "C" __declspec (dllexport)
#	endif

#else

#	define EXPORT

#endif


#endif