#pragma once

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "ticpp-x64-d" )
#pragma comment( lib, "plug-in-x64-d" )
#else if _WIN32
#pragma comment( lib, "ticpp-x86-d" )
#pragma comment( lib, "plug-in-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "ticpp-x64" )
#pragma comment( lib, "plug-in-x64" )
#else if _WIN32
#pragma comment( lib, "ticpp-x86" )
#pragma comment( lib, "plug-in-x86" )
#endif
#endif

#pragma comment( lib, "allegro-debug" )
