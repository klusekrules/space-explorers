// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTLADOWANIAZMIANY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTLADOWANIAZMIANY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTLADOWANIAZMIANY_EXPORTS
#define TESTLADOWANIAZMIANY_API __declspec(dllexport)
#else
#define TESTLADOWANIAZMIANY_API __declspec(dllimport)
#endif

// This class is exported from the TestLadowaniaZmiany.dll
class TESTLADOWANIAZMIANY_API CTestLadowaniaZmiany {
public:
	CTestLadowaniaZmiany(void);
	// TODO: add your methods here.
};

extern TESTLADOWANIAZMIANY_API int nTestLadowaniaZmiany;

TESTLADOWANIAZMIANY_API int fnTestLadowaniaZmiany(void);
