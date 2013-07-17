#pragma once
#include <string>
#include <algorithm>
#include "FuncTransf\ZmianaInterfejs.h"
#include "parser\ticpp.h"

using namespace std;

class Utils
{
public:
	static void trim( string &s){
		s.erase(remove_if(s.begin(), s.end(), isSpace), s.end());
	}

	static bool isSpace( unsigned char c ){
		return isspace(c)!=0;
	}

	static shared_ptr<ZmianaInterfejs> TworzZmiane( TiXmlElement* );
};

