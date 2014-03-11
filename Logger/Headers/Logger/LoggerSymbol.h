#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#ifdef LOGGER_EXPORT

#define LOGGER_API __declspec(dllexport)
#define LOGGER_EXPIMP_TEMPLATE

#elif defined(LOGGER_IMPORT)

#define LOGGER_API __declspec(dllimport)
#define LOGGER_EXPIMP_TEMPLATE extern

#else

#define LOGGER_EXPIMP_TEMPLATE
#define LOGGER_API

#endif
#else

#define LOGGER_EXPIMP_TEMPLATE
#define LOGGER_API

#endif
