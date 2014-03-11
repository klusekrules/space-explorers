#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
	#ifdef ZMIANA_EXPORT
		#define ZMIANA_API __declspec(dllexport)
	#elif defined(ZMIANA_IMPORT)
		#define ZMIANA_API __declspec(dllimport)
	#else
		#define ZMIANA_API
	#endif
#else
	#define ZMIANA_API
#endif
