#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef FUNCTRANSF_EXPORTS
#define FUNCTRANSF_API __declspec(dllexport)
#else
#define FUNCTRANSF_API __declspec(dllimport)
#endif