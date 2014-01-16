#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef LOGGER_EXPORTS
	#define LOGGER_API __declspec(dllexport)
	#define LOGGER_EXPIMP_TEMPLATE
#else
	#define LOGGER_API __declspec(dllimport)
	#define LOGGER_EXPIMP_TEMPLATE extern
#endif