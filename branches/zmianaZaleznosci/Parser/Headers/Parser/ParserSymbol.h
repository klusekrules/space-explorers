#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#   ifdef PARSER_EXPORT
#       define PARSER_API __declspec(dllexport)
#		define PARSER_EXPIMP_TEMPLATE
#   elif defined(PARSER_IMPORT)
#       define PARSER_API __declspec(dllimport)
#		define PARSER_EXPIMP_TEMPLATE extern
#   else
#       define PARSER_API
#   endif
#else
#   define PARSER_API
#endif