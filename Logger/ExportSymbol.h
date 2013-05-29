#pragma once

#ifdef LOGGER_EXPORTS
	#pragma warning( disable : 4251 )
	#define LOGGER_API __declspec(dllexport)
	#define LOGGER_EXPIMP_TEMPLATE
#else
	#define LOGGER_API __declspec(dllimport)
	#define LOGGER_EXPIMP_TEMPLATE extern
#endif