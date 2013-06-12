# -----------------------------------------------------------------------------
# Find DirectX SDK
# Define:
# DirectX_FOUND
# DirectX_INCLUDE_DIR
# DirectX_LIBRARY
# DirectX_ROOT_DIR

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(FindPkgMacros)
  findpkg_begin(DirectX)
  
  # Get path, convert backslashes as ${ENV_DXSDK_DIR}
  getenv_path(DXSDK_DIR)
  getenv_path(DIRECTX_HOME)
  getenv_path(DIRECTX_ROOT)
  getenv_path(DIRECTX_BASE)
  
  # construct search paths
  set(DirectX_PREFIX_PATH 
    "${DXSDK_DIR}" "${ENV_DXSDK_DIR}"
    "${DIRECTX_HOME}" "${ENV_DIRECTX_HOME}"
    "${DIRECTX_ROOT}" "${ENV_DIRECTX_ROOT}"
    "${DIRECTX_BASE}" "${ENV_DIRECTX_BASE}"
    "C:/apps_x86/Microsoft DirectX SDK*"
    "C:/Program Files (x86)/Microsoft DirectX SDK*"
    "C:/apps/Microsoft DirectX SDK*"
    "C:/Program Files/Microsoft DirectX SDK*"
	"$ENV{ProgramFiles}/Microsoft DirectX SDK*"
  )

  # Windows 8 SDK has custom layout
  set(DirectX_INC_SEARCH_PATH 
    "C:/Program Files (x86)/Windows Kits/8.0/Include/shared"
    "C:/Program Files (x86)/Windows Kits/8.0/Include/um"
  )
  set(DirectX_LIB_SEARCH_PATH 
    "C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um"
  )

  create_search_paths(DirectX)
  # redo search if prefix path changed
  clear_if_changed(DirectX_PREFIX_PATH
    DirectX_LIBRARY
	DirectX_INCLUDE_DIR
  )
  
  find_path(DirectX_INCLUDE_DIR NAMES d3d9.h HINTS ${DirectX_INC_SEARCH_PATH})
  # dlls are in DirectX_ROOT_DIR/Developer Runtime/x64|x86
  # lib files are in DirectX_ROOT_DIR/Lib/x64|x86
  if(CMAKE_CL_64)
    set(DirectX_LIBPATH_SUFFIX "x64")
  else(CMAKE_CL_64)
    set(DirectX_LIBPATH_SUFFIX "x86")
  endif(CMAKE_CL_64)
  find_library(DirectX_LIBRARY NAMES d3d9 HINTS ${DirectX_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX_LIBPATH_SUFFIX})
  find_library(DirectX_D3DX9_LIBRARY NAMES d3dx9 HINTS ${DirectX_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX_LIBPATH_SUFFIX})
  find_library(DirectX_DXERR_LIBRARY NAMES DxErr HINTS ${DirectX_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX_LIBPATH_SUFFIX})
  find_library(DirectX_DXGUID_LIBRARY NAMES dxguid HINTS ${DirectX_LIB_SEARCH_PATH} PATH_SUFFIXES ${DirectX_LIBPATH_SUFFIX})
  
  findpkg_finish(DirectX)
  set(DirectX_LIBRARIES ${DirectX_LIBRARIES} 
    ${DirectX_D3DX9_LIBRARY}
    ${DirectX_DXERR_LIBRARY}
    ${DirectX_DXGUID_LIBRARY}
  )
  
  mark_as_advanced(DirectX_D3DX9_LIBRARY DirectX_DXERR_LIBRARY DirectX_DXGUID_LIBRARY
    DirectX_DXGI_LIBRARY DirectX_D3DCOMPILER_LIBRARY)
  
endif()

