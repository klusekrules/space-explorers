#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef FUNCTRANSF_EXPORTS
#define FUNCTRANSF_API __declspec(dllexport)
#else
#define FUNCTRANSF_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "ftrans-x64-d" )
#else if _WIN32
#pragma comment( lib, "ftrans-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "ftrans-x64-r" )
#else if _WIN32
#pragma comment( lib, "ftrans-x86-r" )
#endif
#endif
#endif