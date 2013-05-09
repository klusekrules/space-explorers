// FuncTransf.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "FuncTransf.h"

extern "C" FUNCTRANSF_API bool init(){
		return ZmianaDekorator::RejestrujZmianaDekotor() &&
				ZmianaAgregacja::RejestrujZmianaAgregacja() &&
				ZmianaLiniowa::RejestrujZmianaLiniowa() &&
				ZmianaPotegowa::RejestrujZmianaPotegowa();
	}
