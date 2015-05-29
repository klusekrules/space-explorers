#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#   ifdef NARZEDZIA_EXPORT
#       define NARZEDZIA_API __declspec(dllexport)
#		define NARZEDZIA_EXPIMP_TEMPLATE
#   elif defined(NARZEDZIA_IMPORT)
#       define NARZEDZIA_API __declspec(dllimport)
#		define NARZEDZIA_EXPIMP_TEMPLATE extern
#   else
#       define NARZEDZIA_API 
#   endif
#else
#   define NARZEDZIA_API 
#endif