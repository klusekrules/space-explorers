// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FUNCTRANSF_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FUNCTRANSF_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "ZmianaDekorator.h"
#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"

// This class is exported from the FuncTransf.dll
class FUNCTRANSF_API CFuncTransf {
public:
	CFuncTransf(void);
	// TODO: add your methods here.
};

extern FUNCTRANSF_API int nFuncTransf;

FUNCTRANSF_API int fnFuncTransf(void);
