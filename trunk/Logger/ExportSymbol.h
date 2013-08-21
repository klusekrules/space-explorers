#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef LOGGER_EXPORTS
	#define LOGGER_API __declspec(dllexport)
	#define LOGGER_EXPIMP_TEMPLATE
#else
	#define LOGGER_API __declspec(dllimport)
	#define LOGGER_EXPIMP_TEMPLATE extern
	#ifdef _DEBUG
	#ifdef _WIN64
	#pragma comment( lib, "Logger-x64-d" )
	#else if _WIN32
	#pragma comment( lib, "Logger-x86-d" )
	#endif
	#else
	#ifdef _WIN64
	#pragma comment( lib, "Logger-x64-r" )
	#else if _WIN32
	#pragma comment( lib, "Logger-x86-r" )
	#endif
	#endif
#endif