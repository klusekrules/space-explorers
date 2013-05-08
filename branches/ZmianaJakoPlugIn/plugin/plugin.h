// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PLUGIN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PLUGIN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PLUGIN_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "plug-in-x64-d" )
#else if _WIN32
#pragma comment( lib, "plug-in-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "plug-in-x64" )
#else if _WIN32
#pragma comment( lib, "plug-in-x86" )
#endif
#endif

#endif

// This class is exported from the plugin.dll
class PLUGIN_API Cplugin {
public:
	Cplugin(void);
	// TODO: add your methods here.
};

extern PLUGIN_API int nplugin;

PLUGIN_API int fnplugin(void);
