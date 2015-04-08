#pragma once
#include "git_version.h"

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define VER_FILE_DESCRIPTION_STR    "Built " TIMESTAMP " from " GIT_VERSION 

#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        GIT_VERSION
 
#ifdef _WIN64
	#define VER_PRODUCTNAME_STR         "Space Explorers (64-bit)"
#else
	#define VER_PRODUCTNAME_STR         "Space Explorers (32-bit)"
#endif

#define VER_PRODUCTINTERNALNAME_STR "SpaceExplorers"
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
 
#if LIBRARY_EXPORTS
  #define VER_ORIGINAL_FILENAME_STR VER_PRODUCTINTERNALNAME_STR ".dll"
#else
  #define VER_ORIGINAL_FILENAME_STR VER_PRODUCTINTERNALNAME_STR ".exe"
#endif
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR
 
#define VER_COPYRIGHT_STR           "Copyright (C) 2012-2013"

#define VER_COMPANY_NAME_STR        "N/A"

#ifdef _DEBUG
  #define VER_VER_DEBUG             VS_FF_DEBUG
#else
  #define VER_VER_DEBUG             0
#endif
 
#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
 
#if LIBRARY_EXPORTS
  #define VER_FILETYPE              VFT_DLL
#else
  #define VER_FILETYPE              VFT_APP
#endif

