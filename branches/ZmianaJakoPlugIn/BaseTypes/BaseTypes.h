// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BASETYPES_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BASETYPES_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BASETYPES_EXPORTS
#define BASETYPES_API __declspec(dllexport)
#else
#define BASETYPES_API __declspec(dllimport)
#endif

// This class is exported from the BaseTypes.dll
class BASETYPES_API CBaseTypes {
public:
	CBaseTypes(void);
	// TODO: add your methods here.
};

extern BASETYPES_API int nBaseTypes;

BASETYPES_API int fnBaseTypes(void);
