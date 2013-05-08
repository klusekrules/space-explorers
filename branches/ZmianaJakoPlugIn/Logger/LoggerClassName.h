#pragma once
#include <string>
#include "stdafx.h"
#define CLASSNAME(C) LoggerClassName::className<C>()
/**
* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
* dla klasy generuj¹cej logi z aplikacji.
*/
class LOGGER_API LoggerClassName {
public:	
	/**
	* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
	* \return Nazwa klasy przekazanej przez parametr szablonu.
	*/
	template< class C >
	static std::string className() {
		return std::string(typeid(C).name()).substr(6);
	}
};