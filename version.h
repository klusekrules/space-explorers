#pragma once
#include "svn_version.h"
#include <verrsrc.h>

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)
 
#define VERSION_MAJOR               0
#define VERSION_MINOR               0
#define VERSION_REVISION            2
#define VERSION_BUILD               SVN_REVISION
 
#if SVN_LOCAL_MODIFICATIONS
  #define VERSION_MODIFIER "M"
#else
  #define VERSION_MODIFIER
#endif
 
#define VER_FILE_DESCRIPTION_STR    "Built " STRINGIZE(SVN_TIME_NOW) " from r" STRINGIZE(SVN_REVISION) VERSION_MODIFIER
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD)
 
#define VER_PRODUCTNAME_STR         "Space Explorers"
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

