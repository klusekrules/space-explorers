#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#   ifdef ALGORYTMY_EXPORT
#       define ALGORYTMY_API __declspec(dllexport)
#		define ALGORYTMY_EXPIMP_TEMPLATE
#   elif defined(ALGORYTMY_IMPORT)
#       define ALGORYTMY_API __declspec(dllimport)
#		define ALGORYTMY_EXPIMP_TEMPLATE extern
#   else
#       define ALGORYTMY_API 
#   endif
#else
#   define ALGORYTMY_API 
#endif