#pragma once
#include <string>
#include <algorithm>

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
};

